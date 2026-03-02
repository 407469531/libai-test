
use v5.10;
package dmDump;

require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(dmLibDumpTech dmLibDumpCells dmCellDumpLayerHeaders dmCellDumpInstHeaders 
dmInstHeaderDump dmInstDump dmLayerHeaderDump dmShapeDump dmTextDump dmRectDump 
dmPolyDump dmPathDump dmArrayDump dmLibDumpHeaderMasters dmLibDump dmCellDump dmLayerDump 
dmDump dmHeaderMasterDump);

use smBase;

sub dmLibDumpCells {
    my $lib = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    
    # if lib id is missing, use lib 0
    if (!defined($lib)) {
        $lib = dmLib::get(0);
    }
    
    if (!defined($lib)) {
        print "lib is not defined\n";
        return;
    }

    my @cells;
    my $cellIter = $lib->getCells();
    
    while (my $cell = $cellIter->next()) {
        push @cells, $cell->name();
    }

    foreach my $name (sort @cells) {
        printf("%*scell: %s\n", $indent, "", $name);
    }
}

sub dmLibDumpTech {
    my $lib = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }

    # if lib id is missing, use lib 0
    if (!defined($lib)) {
        $lib = dmLib::get(0);
    }
    
    if (!defined($lib)) {
        print "lib is not defined\n";
        return;
    }
    
    my $tech = $lib->tech();
    printf("%*sdbu per uu: %d\n", $indent, "", $tech->dbuPerUU());
    
    my %layers;

    # iterator all the layerHeaders
    my $iter = $tech->getLayers();
    while (my $layer = $iter->next()) {
        my $key = $layer->layerNum() * 5000 + $layer->dataType();
        $layers{$key} = $layer;
    }

    # have a sorted print out
    foreach my $key (keys %layers) {
        my $layer = $layers{$key};
        dmLayerDump($layer, $indent);
    }
}

sub dmCellDumpLayerHeaders {
    my $cell = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    
    if (!defined($cell)) {
        print "cell is not defined\n";
        return;
    }

    my %layers;

    # iterator all the layerHeaders
    my $iter = $cell->getLayerHeaders();
    while (my $lh = $iter->next()) {
        my $key = $lh->layerNum() * 5000 + $lh->dataType();
        $layers{$key} = $lh;
    }

    # have a sorted print out
    foreach my $key (sort (keys %layers)) {
        my $lh = $layers{$key};
        printf("%*slayer [%d, %d]: (%d, %d)\n", $indent, "", 
                $lh->layerNum(), $lh->dataType(), $lh->count(), $lh->flatCount());
    }
}

sub dmCellDumpInstHeaders {
    my $cell = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    
    if (!defined($cell)) {
        print "cell is not defined\n";
        return;
    }

    my %instHeaders;

    # iterator all the instHeaders
    my $iter = $cell->getInstHeaders();
    while (my $ih = $iter->next()) {
        my $name = $ih->headerMaster()->name();
        $instHeaders{$name} = $ih;
    }

    # have a sorted print out
    foreach my $key (sort (keys %instHeaders)) {
        my $ih = $instHeaders{$key};
        my $master = $ih->master();
        printf("%*sinstheader %s", $indent, "", $key);
        if (!defined($master)) {
            printf("(unbounded)");
        }
        printf(": %d, %d\n", $ih->count(), $ih->flatCount());
    }
}

sub dmInstHeaderDump {
    my $ih = shift;
    my $simple = shift;
    my $indent = shift;

    if (!defined($ih)) {
        print "instHeader is not defined\n";
        return;
    }

    my $iter = $ih->getInsts();
    while (my $inst = $iter->next()) {
        dmInstDump($inst, $simple, $indent);
    }
}

sub dmInstDump {
    my $inst = shift;
    my $simple = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    printf("%*s", $indent);

    if (!defined($simple) || $simple == 0) {
        my $master = $inst->master();
        if ($master) {
            printf("master %s: (%d, %d); ", $master->name());
        } else {
            printf("unbounded inst! ")
        }
    }

    my $bbox = $inst->getBBox();
    my $trans = $inst->transform();
    my $os = $trans->offset();
    my $o = utGetOrientName($trans->orient());
    my $m = $trans->mag();
    printf("inst: BBox(%d, %d, %d, %d), transform: offset(%d, %d), orient:%s, mag:%f\n", 
           $bbox->left(), $bbox->bottom(), $bbox->right(), $bbox->top(), 
           $os->x(), $os->y(), $o, $m);

    if ($inst->type() == $dmObject::ArrayInst) {
        dmArrayDump($inst, $indent);
    }
}

sub dmLayerHeaderDump {
    my $lh = shift;
    my $simple = shift;
    my $indent = shift;

    if (!defined($lh)) {
        print "layerHeader is not defined\n";
        return;
    }

    my $iter = $lh->getShapes();
    while (my $shape = $iter->next()) {
        dmShapeDump($shape, $simple, $indent);
    }
};

sub dmShapeDump {
    my $shape = shift;
    my $simple = shift;   # dump layer number or purpose
    my $indent = shift;

    my $type = $shape->type();

    if ($type == $dmObject::Rect) { dmRectDump($shape, $simple, $indent); }
    elsif ($type == $dmObject::Poly) { dmPolyDump($shape, $simple, $indent); }
    elsif ($type == $dmObject::Path) { dmPathDump($shape, $simple, $indent); }
    elsif ($type == $dmObject::Text) { dmTextDump($shape, $simple, $indent); }
    elsif ($type == $dmObject::RectArray) { 
        dmRectDump($shape, $simple, $indent);
        dmArrayDump($shape, $indent);
    }        
    elsif ($type == $dmObject::PolyArray) { 
        dmPolyDump($shape, $simple, $indent);
        dmArrayDump($shape, $indent);
    }        
    elsif ($type == $dmObject::PathArray) { 
        dmPathDump($shape, $simple, $indent);
        dmArrayDump($shape, $indent);
    }
    elsif ($type == $dmObject::TextArray) { 
        dmTextDump($shape, $simple, $indent);
        dmArrayDump($shape, $indent);
    }
    else { printf "shape type error!\n"; }

};

sub dmRectDump {
    my $rect = shift;
	my $simple = shift;
	my $indent = shift;
	if (!defined($indent)) { $indent = 0; }
    printf("%*s", $indent);

	if (!defined($simple) || $simple == 0) {
        my $lh = $rect->layerHeader();
        printf("layer:(%d, %d)  ", $lh->layerNum(), $lh->dataType());
    }
    my $box = $rect->getBBox();	
    printf("dmRect: box: (%d, %d, %d, %d) \n",
        $box->left(), $box->bottom(), $box->right(), $box->top());
};

sub dmPolyDump {
    my $dmPoly = shift;	
	my $simple = shift;
	my $indent = shift;
	if (!defined($indent)) { $indent = 0; }	
    printf("%*s", $indent);

	if (!defined($simple) || $simple == 0) {
          my $lh = $dmPoly->layerHeader();
          printf("layer:(%d, %d)  ", $lh->layerNum(), $lh->dataType());
    }
	my $utPolygon = $dmPoly->getPolygon();
    my $bbox = $dmPoly->getBBox();
	printf("dmPoly: bbox: (%d, %d, %d, %d) \n",
           $bbox->left(), $bbox->bottom(), $bbox->right(), $bbox->top());
		   
	for (my $it = 0; $it < $utPolygon->size(); $it++) {
		printf("%*s%d: (%d, %d) \n" , $indent == 0 ? 4 : $indent * 2, "", $it, 
               $utPolygon->{$it}->x(), $utPolygon->{$it}->y() );
	}
};

sub dmPathDump {
    my $dmPath = shift; 
	my $simple = shift;
	my $indent = shift;
	if (!defined($indent)) { $indent = 0; }  
    printf("%*s", $indent);

	if (!defined($simple) || $simple == 0) {
       my $lh = $dmPath->layerHeader();
       printf("layer:(%d, %d)  ", $lh->layerNum(), $lh->dataType());
	}
    my $utPath = $dmPath->getPath();
	my $bbox = $dmPath->getBBox();
	printf("dmPath: bbox: (%d, %d, %d, %d), halfWidth: %u, style: %s, beginExt: %u, endExt:%u\n",
           $bbox->left(), $bbox->bottom(), $bbox->right(), $bbox->top(),
            $utPath->halfWidth(), utPathStyleName($utPath->style()), $utPath->beginExt(), $utPath->endExt());

	for (my $it = 0; $it < $utPath->size(); $it++) {
    	printf("%*s%d: (%d, %d) \n" , $indent == 0 ? 4 : $indent * 2, "", $it, 
               $utPath->{$it}->x(), $utPath->{$it}->y());
    }
};

sub utPathStyleName {
    my $s = shift;
    if ($o == 0) { return "Truncate"; }
    elsif ($o == 1) { return "HalfWidth"; }
    elsif ($o == 2) { return "Round"; }
    elsif ($o == 3) { return "Custom"; }        
    else { return "Truncate"; }
};

sub dmTextDump {
    my $text = shift;
    my $simple = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    printf("%*s", $indent);

    my $bbox = $text->getBBox();
    my $str = $text->getText();
    if (!defined($simple) || $simple == 0) {
        my $lh = $text->layerHeader();
        printf("layer:(%d, %d)  ", $lh->layerNum(), $lh->dataType());
    }
    printf("text: %s, BBox(%d, %d, %d, %d)\n",
            $str->text(), $bbox->left(), $bbox->bottom(), $bbox->right(), $bbox->top());
}

sub dmArrayDump {
    my $array = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 4; }
    printf("%*s", $indent);

    my $ay = $array->getArray();
    printf("Array: nx:%d, ny:%d, a11:%d, a22:%d, a12:%d, a21:%d\n",
            $ay->nx(), $ay->ny(), $ay->a11(), $ay->a22(), $ay->a12(), $ay->a21());
}

sub utGetOrientName {
    my $o = shift;
    if ($o == 0) { return "utR0"; }
    elsif ($o == 1) { return "utMX"; }
    elsif ($o == 2) { return "utMY"; }
    elsif ($o == 3) { return "utR180"; }
    elsif ($o == 4) { return "utMX90"; }
    elsif ($o == 5) { return "utR90"; }
    elsif ($o == 6) { return "utR270"; }
    else { return "utMY90"; }
}

sub dmLibDumpHeaderMasters {
    my $lib = shift;
    my $indent = shift;
    if (!defined($indent)) { $indent = 0; }
    
    # if lib id is missing, use lib 0
    if (!defined($lib)) {
        $lib = dmLib::get(0);
    }
    
    if (!defined($lib)) {
        print "lib is not defined\n";
        return;
    }
    
    my @names;
    my $iter = $lib->getHeaderMasters();
    while (my $hm = $iter->next()) {
        push @names, $hm->name();
    }

    foreach my $n (sort @names) {
        printf("%*sheader master: %s\n", $indent, "", $n);
    }
}

sub dmLibDump {
    my $lib = shift;
    
    # if lib id is missing, use lib 0
    if (!defined($lib)) {
        $lib = dmLib::get(0);
    }
    
    if (!defined($lib)) {
        print "lib is not defined\n";
        return;
    }
    
    printf("-----------------Tech-----------------\n");
    dmLibDumpTech($lib, 4);
    printf("-----------------Cells----------------\n");
    dmLibDumpCells($lib, 4);
}

sub dmCellDump {   
    my $cell = shift;
    
    if (!defined($cell)) {
        print "cell is not defined\n";
        return;
    }
    
    printf("-------------Layer Headers--------------\n");
    dmCellDumpLayerHeaders($cell, 4);
    printf("-------------Inst Headers---------------\n");
    dmCellDumpInstHeaders($cell, 4);
}

sub dmLayerDump {
	my $layer = shift;
	my $indent = shift;
	if (!defined($indent)) { $indent = 0; }
	if (!defined($layer)) {
        print "layer is not defined\n";
        return;
    }
	printf("%*slayer [%d, %d], name: %s\n", $indent, "",
       $layer->layerNum(), $layer->dataType(), $layer->name());
}

sub dmHeaderMasterDump {
    my $hm = shift;
    my $indent = shift;
	if (!defined($indent)) { $indent = 0; }
    if (!defined($hm)) {
        print "header master is not defined\n";
        return;
    }
    
    printf("%*sHeader Master %s", $indent, "", $hm->name());
    my $master = $hm->master();
    if (!defined($master)) {
        printf("(unbound): \n");
    } else {
        printf(": \n");
    }

    my $iter = $hm->getInstHeaders();
    while (my $ih = $iter->next()) {
        my $pcell = $ih->cell();
        printf("%*sin cell %s: (%d, %d)\n", $indent == 0 ? 4 : $indent * 2, "",
                $pcell->name(), $ih->count(), $ih->flatCount());
    }
}

sub dmDump {
    my $obj = shift;

    if (!defined($obj)) {
        print "object is not defined\n";
        return;
    }

    my $type = $obj->type();
    if ($type == $dmObject::Cell) { dmCellDump($obj); }
    elsif ($type == $dmObject::Layer) { dmLayerDump($obj); }
    elsif ($type == $dmObject::LayerHeader) { dmLayerHeaderDump($obj); }
    elsif ($type == $dmObject::InstHeader) { dmInstHeaderDump($obj); }
    elsif ($type == $dmObject::HeaderMaster) { dmHeaderMasterDump($obj); }
    else {
        if ($obj->isInst()) {
            dmInstDump($obj);
        } else {
            dmShapeDump($obj);
        }
    }

}

1;
