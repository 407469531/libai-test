
package dmLibExpand;
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(smGetLayers smTopCell smCopyLayer smShifted smGetDbu smQuery smGridsnap openPSLayoutViewer);
use smBase;

sub smGetLayers {
    my $lib = shift;
    if(!defined($lib)) {
        print "lib error!!!\n";
        return;
    }
    
    my $cellName = shift;
    my $layerName = shift;
    my @result;

    if(!defined($cellName)) {
        my $lIt = $lib->tech()->getLayers();
        while(my $layer = $lIt->next()) {
            if(!defined($layerName) || ($layer->name() eq $layerName)) {
                my $lpp = $layer->layerNum().'.'.$layer->dataType();
                push(@result, $lpp);
            }       
        }
    } else {
        my $cell = $lib->findCell($cellName);
        if(!defined($cell)) {
            print "cell not exist!!!\n";
            return;
        }
        my $lhIt = $cell->getLayerHeaders();
        while(my $lh = $lhIt->next()) {
            my $lpp = $lh->layerNum().'.'.$lh->dataType();
            if(!defined($layerName)) {
                push(@result, $lpp)
            } else {
                my $layer = $lib->tech()->findLayer($lpp);
                if(!defined($layer) && ($layer->name() eq $layerName)) {
                    my $lpp = $layer->layerNum().'.'.$layer->dataType();
                    push(@result, $lpp);
                }
            }
        }
    }
    return @result;
}

sub smTopCell {
    my $lib = shift;
    if(!defined($lib)) {
        print "lib error!!!\n";
        return;
    }
    my $all = shift;
    my @result;

    if(!defined($all) || $all eq 0) {
        my $cell = $lib->curCell();
        push(@result, $cell->name());
    } else {
        my $cIt = $lib->getCells();
        while($it = $cIt->next()) {
            if($it->isTopCell()) {
                push(@result, $it->name());   
            }
        }
    }
    return @result;
}

sub smCopyLayer {
    my $lib = shift;
    if (!defined($lib)) {
        print "lib error!\n";
        return;
    }

    my $lpp1 = shift;
    if (!defined($lpp1)) {
        print "layer1 is required!\n";
        return;
    }

    my $lpp2 = shift;
    if (!defined($lpp2)) {
        print "layer2 is required!\n";
        return;
    }

    if ($lpp1 =~ /^\d+$/) {
        $lpp1 = sprintf("%.1f", $lpp1);
    } elsif ($lpp1 !~ /^(\d+)\.?(\d+)$/) {
        print "layer1 is illegal!\n";
        return;
    }

    if ($lpp2 =~ /^\d+$/) {
        $lpp2 = sprintf("%.1f", $lpp2);
    } elsif ($lpp2 !~ /^(\d+)\.?(\d+)$/) {
        print "layer2 is illegal!\n";
        return;
    }

    smDBc::smEnableUndoRedo(0);
    my $lay1 = $lib->tech()->findLayer($lpp1);
    if (!defined($lay1)) {
        print "layer1 does not exist or is empty!\n";
        return;
    } else {
        my ($layerNum1, $dataType1) = split(/\./, $lpp1);
        my ($layerNum2, $dataType2) = split(/\./, $lpp2);     
        my $cells = $lib->getCells();
        while (my $cell = $cells->next()) {
            my $lh1 = $cell->getLayerHeader($layerNum1, $dataType1);
            my $lh2 = $cell->getLayerHeader($layerNum2, $dataType2);
            my $shpIter = $lh1->getShapes();
            while (my $shape = $shpIter->next()) {
                my $type = $shape->type();
                if ($type == $dmObject::Rect) {
                    $lh2->createRect($shape->box());
                } elsif ($type == $dmObject::RectArray) {
                    $lh2->createRectArray($shape->box(), $shape->getArray());
                } elsif ($type == $dmObject::Poly) {
                    $lh2->createPoly($shape->getPolygon());
                } elsif ($type == $dmObject::PolyArray) {
                    $lh2->createPolyArray($shape->getPolygon(), $shape->getArray());
                } elsif ($type == $dmObject::Path) {
                    $lh2->createPath($shape->getPath());
                } elsif ($type == $dmObject::PathArray) {
                    $lh2->createPathArray($shape->getPath(), $shape->getArray());
                } elsif ($type == $dmObject::Text) {
                    $lh2->createText($shape->getText());
                } elsif ($type == $dmObject::TextArray) {
                    $lh2->createTextArray($shape->getText(), $shape->getArray());
                } 
            }
        }
    }
    smDBc::smEnableUndoRedo(1);
}

sub smShifted {
    my $lib = shift;
    if (!defined($lib)) {
        print "lib error!\n";
        return;
    }

    my $cellName = shift;
    if (!defined($cellName)) {
        print "cellName not defined!\n";
        return;
    }

    my $x = shift;
    if (!defined($x)) {
        print "x is required!\n";
        return;
    }

    my $y = shift;
    if (!defined($y)) {
        print "y is required!\n";
        return;
    }

    my $dbuu = $lib->tech()->dbuPerUU();
    my $xUnit = 'd', $yUnit = 'd';

    if ($x =~ /^([+-]?\d+\.?\d+)([du])$/) {
        $x = $1;
        $xUnit = $2;
    } elsif ($x !~ /^([+-]?\d+\.?\d+)$/) {
        print "x is illegal!\n";
        return;
    }

    if ($y =~ /^([+-]?\d+\.?\d+)([du])$/) {
        $y = $1;
        $yUnit = $2;
    } elsif ($y !~ /^([+-]?\d+\.?\d+)$/) {
        print "y is illegal!\n";
        return;
    }

    if ($xUnit eq 'u') {
        $x = sprintf("%.0f", $x * $dbuu);
    } else {
        $x = int($x);
    }

    if ($yUnit eq 'u') {
        $y = sprintf("%.0f", $y * $dbuu);
    } else {
        $y = int($y);
    }

    my $shiftPoint = new utPoint(-$x, -$y);
    my $cell = $lib->findCell($cellName);
    if (!defined($cell) || $cell == 0) {
        print "cell $cellName does not exist!\n";
        return;
    }

    smDBc::smEnableUndoRedo(0);
    my $lhIter = $cell->getLayerHeaders();
    while (my $lh = $lhIter->next()) {
        my $shpIter = $lh->getShapes();
        while (my $shape = $shpIter->next()) {
            if ($shape->type() == $dmObject::Rect || $shape->type() == $dmObject::RectArray) {
                $shape->setBox($shape->box()->shifted($shiftPoint));
            } elsif ($shape->type() == $dmObject::Poly || $shape->type() == $dmObject::PolyArray) {
                my $poly = $shape->getPolygon();
                $poly->shift($shiftPoint);
                $shape->setPolygon($poly);
            } elsif ($shape->type() == $dmObject::Path || $shape->type() == $dmObject::PathArray) {
                my $path = $shape->getPath();
                for(my $i = 0; $i < $path->size(); $i++) {
                    $path->{$i}->shift(-$x, -$y);
                }
                $shape->setPath($path);
            } elsif ($shape->type() == $dmObject::Text || $shape->type() == $dmObject::TextArray) {
                my $text = $shape->getText();
                $text->setOrigin($text->origin()->shifted(-$x, -$y));
                $shape->setText($text);
            }
        }
    }

    my $ihIter = $cell->getInstHeaders();
    while (my $ih = $ihIter->next()) {
        my $instIter = $ih->getInsts();
        while (my $inst = $instIter->next()) {
            $inst->setTransform($inst->transform()->shifted($shiftPoint));
        }
    }

    my $ignoreInst = shift;
    if (defined($ignoreInst) && !$cell->isTopCell()) {
        my $insShiftPoint = new utPoint($x, $y);
        my $ihIter =  $lib->findHeaderMaster($cell)->getInstHeaders();
        while (my $ih = $ihIter->next()) {
            my $instIter = $ih->getInsts();
            while (my $inst = $instIter->next()) {
                $inst->setTransform($inst->transform()->shifted($insShiftPoint));
            }
        }
    }
    smDBc::smEnableUndoRedo(1);
}

sub smGetDbu {
    my $in = shift;
    if (!defined($in)) {
        print "smGetDbu input not defined!\n";
        return undef;
    }

    my $unit = 'd';
    if ($in =~ /^([+-]?\d+(\.\d+)?)([du])$/) {
        $in = $1;
        $unit = $3;
    } elsif ($in !~ /^[+-]?\d+(\.\d+)?$/) {
        print "smGetDbu input invalid!\n";
        return undef;
    }

    if ($unit eq 'u') {
        my $dbuu = shift;
        if (!defined($dbuu) || $dbuu !~ /^\d+$/) {
            print "smGetDbu dbuu not defined or invalid!\n";
            return undef;
        }
        $in = sprintf("%.0f", $in * $dbuu);
    } elsif ($unit eq 'd') {
        $in = int($in);
    } else {
        print "smGetDbu unit $unit invalid!\n";
        return undef;
    }

    return $in;
}

sub smQuery {
    my $libId = shift;
    if (!defined($libId)) {
        print "ERROR: libId not defined!\n";
        return;
    }
    my $lib = dmLib::find($libId);
    if (!$lib) {
        print "ERROR: libId $libId invalid!\n";
        return;
    }

    my $objType = shift;
    if (!defined($objType)) {
        print "ERROR: objType not defined!\n";
        return;
    }

    my $cellName = shift;
    if (!defined($cellName)) {
        print "ERROR: cellName not defined!\n";
        return;
    }
    my $top = $lib->findCell($cellName);
    if (!defined($top) || $top == 0) {
        print "ERROR: cell '$cellName' does not exist in lib $libId!\n";
        return;
    }

    my $startDepth = shift;
    if (!defined($startDepth)) {
        print "ERROR: startDepth not defined!\n";
        return;
    } elsif  ($startDepth !~ /^\d+$/) {
        print "ERROR: startDepth invalid!\n";
        return;
    }

    my $endDepth = shift;
    if (!defined($endDepth)) {
        print "ERROR: endDepth not defined!\n";
        return;
    } elsif  ($endDepth !~ /^\d+$/) {
        print "ERROR: endDepth invalid!\n";
        return;
    }

    if ($startDepth > $endDepth) {
        print "ERROR: startDepth > endDepth!\n";
        return;
    }

    my $dbuu = $lib->tech()->dbuPerUU();

    my $x = shift;
    if (!defined($x)) {
        print "ERROR: x not defined!\n";
        return;
    } elsif (!defined($x = smGetDbu($x, $dbuu))) {
        print "ERROR: x invalid!\n";
        return;
    }

    my $y = shift;
    if (!defined($y)) {
        print "ERROR: y not defined!\n";
        return;
    } elsif (!defined($y = smGetDbu($y, $dbuu))) {
        print "ERROR: y invalid!\n";
        return;
    }

    my $path = shift;
    my $pathlist = shift;
    my $inside = shift;

    if ($path && $pathlist) {
        print "ERROR: -path and -pathlist option should not be both used!\n";
        return;
    }

    my $maxSDX = shift; 
    if ($inside) {
        if (defined($maxSDX)) {
            print "WARNING: maxSearchDistanceX will be ignored as -inside used!\n"; 
        }
        $maxSDX = 0;
    } elsif (!defined($maxSDX)) {
        $maxSDX = $dbuu;
    } elsif (!defined($maxSDX = smGetDbu($maxSDX, $dbuu)) || $maxSDX < 0) {
        print "ERROR: maxSearchDistanceX invalid!\n";
        return;
    }

    my $maxSDY = shift;
    if ($inside) {
        if (defined($maxSDY)) {
            print "WARNING: maxSearchDistanceY will be ignored as -inside used!\n";
        }
        $maxSDY = 0;
    } elsif (!defined($maxSDY)) {
        $maxSDY = $dbuu;
    } elsif (!defined($maxSDY = smGetDbu($maxSDY, $dbuu)) || $maxSDY < 0) {
        print "ERROR: maxSearchDistanceY invalid!\n";
        return;
    }


    printf("Left bottom point: (%d, %d), right top point: (%d, %d)\n", $x - $maxSDX / 2, $y - $maxSDY / 2, $x + $maxSDX / 2, $y + $maxSDY / 2);

    my $queryInfo = new edQueryInfo($top, $objType, $x, $y, $maxSDX, $maxSDY, $startDepth, $endDepth, $path, $pathlist, $inside);
    my $resExist = $queryInfo->printInfo();
    if (!$resExist) {
        print "No shapes or instances queried!\n";
    }
}

sub smGridsnap {
    smDBc::smEnableUndoRedo(0);

    my $libId = shift;
    if (!defined($libId)) {
        print "ERROR: lib $libId not defined!\n";
        return;
    }

    my $lib = dmLib::find($libId);
    if (!defined($lib)) {
        print "ERROR: lib $libId does not exist!\n";
        return;
    }

    my $gridSize = shift;
    my $gridDbu = undef;
    if (!defined($gridSize)) {
        print "ERROR: gridsize not defined or invalid!\n";
        return;
    } else {
        my $dbuu = $lib->tech()->dbuPerUU();
        my $precision = 1.0 / $dbuu;
        if ($gridSize < $precision) {
            print "ERROR: gridsize(microns) value is smaller than precision of the layout!\n";
            return;
        } else {
            $gridDbu = $gridSize * $dbuu;
            if ($gridDbu =~ /^\d+\.\d+$/) {
                print "WARNING: gridsize value will rounded!\n";
                $gridDbu = sprintf("%.0f", $gridDbu);
                $gridSize = $gridDbu / $dbuu;
            }
        }
    }

    my $checkonly = shift;
    my ($layerNum, $dataType) = undef;
    if (!defined($checkonly)) {
        print "ERROR: checkonly not defined!\n";
        return;
    } elsif ($checkonly) {
        if (!defined($layer = shift) || $layer !~ /^\d+(\.\d+)$/) {
            print "ERROR: layer not defined or invalid!\n";
            return;
        } else {
            ($layerNum, $dataType) = split(/\./, $layer);

        }
    }

    my $c = shift;
    my $cellName = "";
    my $cell = undef;
    if (!defined($c)) {
        print "ERROR: c not defined!\n";
        return;
    } elsif ($c) {
        if (!defined($cellName = shift)) {
            print "ERROR: cellName not defined as c used!\n";
            return;
        }
        $cell = $lib->findCell($cellName);
        if (!defined($cell)) {
            print "ERROR: cell $cellName does not exist in lib $libId!\n";
            return;
        }    
    } 

    my $res = 0;
    if ($c) {
        my $snap;
        if ($checkonly) {
            my $newLay = $cell->getLayerHeader($layerNum, $dataType);
            $snap = new edSnapCell($cell, $gridDbu, $newLay);
        } else {
            $snap = new edSnapCell($cell, $gridDbu);
        }

        $res += $snap->snapGrid();
    } else {
        my $cIter =$lib->getCells();
        while (my $cell = $cIter->next()) {
            my $snap;
            if ($checkonly) {
                my $newLay = $cell->getLayerHeader($layerNum, $dataType);
                $snap = new edSnapCell($cell, $gridDbu, $newLay);
            } else {
                $snap = new edSnapCell($cell, $gridDbu);

            }
 
            $res += $snap->snapGrid();
        }
    }

    print "snaped obejects: $res\n";
    smDBc::smEnableUndoRedo(1);
    return $res;
}

sub openPSLayoutViewer {
    my ($layoutPath, $level, $outputPath) = @_;
    $Form::patternSearch->close();
    my $lib = smOpenDesign($layoutPath);

    if (!defined($lib)) {
        print "ERROR: invalid input file: '$layoutPath' !\n";
        return;
    }

    smSetLevel($level, $lib->libId());
    $Form::patternSearch->show($lib->libId());
    $Form::patternSearch->{'PatternPath'} = $outputPath;
}


1;
