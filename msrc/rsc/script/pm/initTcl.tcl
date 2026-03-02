proc registerForm {fname} {
    set handle [pmGetForm $fname]
    interp alias {} Form::$fname {} dispatch $handle
}

proc dispatch {handle method args} {
    if {[string match "*_*" $method]} {
        uplevel 1 [list $method $handle {*}$args]
    } else {
        uplevel 1 [list $handle $method {*}$args]
    }
}

proc smSaveAs {args} {
    array set hash {
        libId 0
        path ""
        format ""
        cell ""
        layerMap ""
        visibleOnly 0
        emptyCell 0
        unboundInstance 1
        dbUU 0
        scalingFactor 1.0
    }
    array set input $args
    foreach key [array names input] {
        if {[info exists hash($key)]} {
            set hash($key) $input($key)
        }
    }
    edSaveAs $hash(libId) $hash(path) $hash(format) $hash(cell) $hash(layerMap) $hash(visibleOnly) $hash(emptyCell) $hash(unboundInstance) $hash(dbUU) $hash(scalingFactor)
}

array set data {}

proc smCreateAllUserForm {} {
    set form [pmCreateUserForm "test"]
    global data
    set data(test) $form
}

proc smUserApply {name lib} {
    global data
    set form $data($name)
    set cv [$form pmUserForm_controlValue "cell"]
    puts "$name,$lib,$cv"
}

proc smAddControls {name} {
    global data
    set form $data($name)
    $form pmUserForm_addCellSelection "cell" 0 0
    $form pmUserForm_addLayerSelection "layer" 1 0
}

proc dmLibDumpCells {lib {indent 0}} {
    if {$lib eq ""} {
        set lib [dmLib_get 0]
    }
    
    if {$lib eq ""} {
        puts "lib is not defined"
        return
    }
    
    set cells {}
    set cellIter [dmLib_getCells $lib]
    
    while {[set cell [$cellIter next]] ne ""} {
        lappend cells [dmCell_name $cell]
    }
    
    foreach name [lsort $cells] {
        puts [format "%*scell: %s" $indent "" $name]
    }
} 

proc dmLibDumpTech {lib {indent 0}} {
    if {$lib eq ""} {
        set lib [dmLib_get 0]
    }
    
    if {$lib eq ""} {
        puts "lib is not defined"
        return
    }
    
    set tech [dmLib_tech $lib]
    puts [format "%*sdbu per uu: %d" $indent "" [dmTech_dbuPerUU $tech]
    
    array unset layers

    set iter [dmTech_getLayers $tech]
    while {[set layer [$iter next]] ne ""} {
        set key [expr {[dmLayerHeader_layerNum $layer] * 5000 + [dmLayerHeader_dataType $layer]}]
        set layers($key) $layer
    }
    
    foreach key [lsort -integer [array names layers]] {
        set layer $layers($key)
        dmLayerDump $layer $indent
    }
}

proc dmCellDumpLayerHeaders {cell {indent 0}} {
    if {$cell eq ""} {
        puts "cell is not defined"
        return
    }
    
    array unset layers
    
    set iter [dmCell_getLayerHeaders $cell]
    while {[set lh [$iter next]] ne ""} {
        set key [expr {[dmLayerHeader_layerNum $lh] * 5000 + [dmLayerHeader_dataType $lh]}]
        set layers($key) $lh
    }
    
    foreach key [lsort -integer [array names layers]] {
        set lh $layers($key)
        puts [format "%*slayer [%d, %d]: (%d, %d)" $indent "" \
               [dmLayerHeader_layerNum $lh] [dmLayerHeader_dataType $lh ] [dmLayerHeader_count $lh] [dmLayerHeader_flatCount $lh]]
    }
}

proc dmCellDumpInstHeaders {cell {indent 0}} {
    if {$cell eq ""} {
        puts "cell is not defined"
        return
    }
    
    array unset instHeaders
    
    set iter [dmCell_getInstHeaders $cell]
    while {[set ih [$iter next]] ne ""} {
        set name [dmCell_name [dmInstHeader_headerMaster $ih]]
        set instHeaders($name) $ih
    }
    
    foreach key [lsort [array names instHeaders]] {
        set ih $instHeaders($key)
        set master [dmInstHeader_master $ih]
        puts -nonewline [format "%*sinstheader %s" $indent "" $key]
        if {$master eq ""} {
            puts -nonewline "(unbounded)"
        }
        puts [format ": %d, %d" [dmInstHeader_count $ih] [dmInstHeader_flatCount $ih]]
    }
}


proc dmInstHeaderDump {ih {simple 0} {indent 0}} {
    if {$ih eq ""} {
        puts "instHeader is not defined"
        return
    }
    
    set iter [dmInstHeader_getInsts $ih]
    while {[set inst [$iter next]] ne ""} {
        dmInstDump $inst $simple $indent
    }
}

proc dmInstDump {inst {simple 0} {indent 0}} {
    global dmObject_ArrayInst
    if {$inst eq ""} {
        return
    }
    
    puts -nonewline [format "%*s" $indent ""]
    
    if {$simple eq "" || $simple == 0} {
        set master [$inst master]
        if {$master ne ""} {
            puts -nonewline [format "master %s: (0, 0); " [dmCell_name $master]]
        } else {
            puts -nonewline "unbounded inst! "
        }
    }
    
    set bbox [dmFig_getBBox $inst]
    set trans [dmInst_transform $inst]
    set os [utTransform_offset $trans]
    set o [utGetOrientName [utTransform_orient $trans]]
    set m [utTransform_mag $trans]
    puts [format "inst: BBox(%d, %d, %d, %d), transform: offset(%d, %d), orient:%s, mag:%f" \
    [utBox_left $bbox] [utBox_bottom $bbox] [utBox_right $bbox] [utBox_top $bbox]  [utPoint_x $os] [utPoint_y $os]  $o $m]
    
    if {[dmObject_type $inst] == $dmObject_ArrayInst} {
        dmArrayDump $inst $indent
    }
}


proc dmLayerHeaderDump {lh {simple 0} {indent 0}} {
    if {$lh eq ""} {
        puts "layerHeader is not defined"
        return
    }
    
    set iter [dmLayerHeader_getShapes $lh]
    while {[set shape [$iter next]] ne ""} {
        dmShapeDump $shape $simple $indent
    }
}

proc dmRectDump {rect {simple 0} {indent 0}} {
    if {$rect eq ""} {
        return
    }
    
    puts -nonewline [format "%*s" $indent ""]
    
    if {$simple eq "" || $simple == 0} {
        set lh [dmShape_layerHeader $rect]
        puts -nonewline [format "layer:(%d, %d)  " [dmLayerHeader_layerNum $lh] [dmLayerHeader_dataType $lh]]
    }
    
    set bbox [dmFig_getBBox $rect]
    puts [format "dmRect: box: (%d, %d, %d, %d)" \
            [utBox_left $bbox] [utBox_bottom $bbox] [utBox_right $bbox] [utBox_top $bbox]]
}

proc utPathStyleName {s} {
    switch $s {
        0 { return "Truncate" }
        1 { return "HalfWidth" }
        2 { return "Round" }
        3 { return "Custom" }
        default { return "Truncate" }
    }
} 

proc dmPolyDump {dmPoly {simple 0} {indent 0}} {
    if {$dmPoly eq ""} {
        return
    }
    puts -nonewline [format "%*s" $indent ""]
    
    if {$simple eq "" || $simple == 0} {
        set lh [dmShape_layerHeader $dmPoly]
        puts -nonewline [format "layer:(%d, %d)  " [dmLayerHeader_layerNum $lh] [dmLayerHeader_dataType $lh]]
    }
    set utPolygon [$dmPoly getPolygon]
    set bbox [dmFig_getBBox $dmPoly]
    puts [format "dmPoly: bbox: (%d, %d, %d, %d)" \
            [utBox_left $bbox] [utBox_bottom $bbox] [utBox_right $bbox] [utBox_top $bbox]]
    
    set size [$utPolygon size]
    for {set it 0} {$it < $size} {incr it} {
        set point [$utPolygon FETCH $it]
        puts [format "%*s%d: (%d, %d)" [expr {$indent == 0 ? 4 : $indent * 2}] "" $it [utPoint_x $point] [utPoint_y $point]]
    }
}

proc dmPathDump {dmPath {simple 0} {indent 0}} {
    if {$dmPath eq ""} {
        return
    }
    
    puts -nonewline [format "%*s" $indent ""]
    
    if {$simple eq "" || $simple == 0} {
        set lh [dmShape_layerHeader $dmPath]
        puts -nonewline [format "layer:(%d, %d)  " [dmLayerHeader_layerNum $lh] [dmLayerHeader_dataType $lh]]
    }
    
    set utPath [$dmPath getPath] 
    set bbox [dmFig_getBBox $dmPath]
    puts [format "dmPath: bbox: (%d, %d, %d, %d), halfWidth: %u, style: %s, beginExt: %u, endExt:%u" \
            [utBox_left $bbox] [utBox_bottom $bbox] [utBox_right $bbox] [utBox_top $bbox] \ [utPath_halfWidth $utPath] [utPathStyleName [utPath_style $utPath]] [utPath_beginExt $utPath] [utPath_endExt $utPath]]
    
    set size [$utPath size]
    for {set it 0} {$it < $size} {incr it} {
        set point [$utPath FETCH $it]
        puts [format "%*s%d: (%d, %d)" [expr {$indent == 0 ? 4 : $indent * 2}] "" $it [utPoint_x $point] [utPoint_y $point]]
    }
}

proc dmTextDump {text {simple 0} {indent 0}} {
    if {$text eq ""} {
        return
    }
    
    puts -nonewline [format "%*s" $indent ""]
    
    set bbox [dmFig_getBBox $text]
    set str [$text getText]
    
    if {$simple eq "" || $simple == 0} {
        set lh [dmShape_layerHeader $text]
        puts -nonewline [format "layer:(%d, %d)  " [dmLayerHeader_layerNum $lh] [dmLayerHeader_dataType $lh]]
    }
    
    puts [format "text: %s, BBox(%d, %d, %d, %d)" [$str text] [utBox_left $bbox] [utBox_bottom $bbox] [utBox_right $bbox] [utBox_top $bbox]]
}

proc dmArrayDump {array {indent 4}} {
    if {$array eq ""} {
        return
    }
    puts -nonewline [format "%*s" $indent ""]
    set ay [$array getArray]
    puts [format "Array: nx:%d, ny:%d, a11:%d, a22:%d, a12:%d, a21:%d" \
            [utArray_nx $ay] [utArray_ny $ay] [utArray_a11 $ay] [utArray_a22 $ay] [utArray_a12 $ay] [utArray_a21 $ay]]
}

proc utGetOrientName {orient} {
    switch $orient {
        0 { return "utR0" }
        1 { return "utMX" }
        2 { return "utMY" }
        3 { return "utR180" }
        4 { return "utMX90" }
        5 { return "utR90" }
        6 { return "utR270" }
        default { return "utMY90" }
    }
}

proc dmLibDumpHeaderMasters {lib {indent 0}} {
    if {$lib eq ""} {
        set lib [dmLib_get 0]
    }
    
    if {$lib eq ""} {
        puts "lib is not defined"
        return
    }
    
    set names {}
    set iter [dmLib_getHeaderMasters $lib]
    while {[set hm [$iter next]] ne ""} {
        lappend names [$hm name]
    }
    
    foreach n [lsort $names] {
        puts [format "%*sheader master: %s" $indent "" $n]
    }
}

proc dmLibDump {lib} {
    if {$lib eq ""} {
        set lib [dmLib_get 0]
    }
    
    if {$lib eq ""} {
        puts "lib is not defined"
        return
    }
    
    puts "-----------------Tech-----------------"
    dmLibDumpTech $lib 4
    puts "-----------------Cells----------------"
    dmLibDumpCells $lib 4
}

proc dmCellDump {cell} {
    if {$cell eq ""} {
        puts "cell is not defined"
        return
    }
    
    puts "-------------Layer Headers--------------"
    dmCellDumpLayerHeaders $cell 4
    puts "-------------Inst Headers---------------"
    dmCellDumpInstHeaders $cell 4
}

proc dmLayerDump {layer {indent 0}} {
    if {$layer eq ""} {
        puts "layer is not defined"
        return
    }
    
    set layer_num [dmLayerHeader_layerNum $layer]
    set data_type [dmLayerHeader_dataType $layer]
    set name [dmLayerHeader_name $layer]
    puts [format "%*slayer [%d, %d], name: %s" $indent "" $layer_num $data_type $name]
}

proc dmHeaderMasterDump {hm {indent 0}} {
    if {$hm eq ""} {
        puts "header master is not defined"
        return
    }
    
    set name [$hm name]
    puts -nonewline [format "%*sHeader Master %s" $indent "" $name]
    
    set master [$hm master]
    if {$master eq ""} {
        puts "(unbound): "
    } else {
        puts ": "
    }
    
    set iter [dmHeaderMaster_getInstHeaders $hm]
    while {[set ih [$iter next]] ne ""} {
        set pcell [dmInstHeader_cell $ih]
        set pcell_name [dmCell_name $pcell]
        set count [$ih dmInstHeader_count]
        set flat_count [$ih dmInstHeader_flatCount]
        puts [format "%*sin cell %s: (%d, %d)" [expr {$indent == 0 ? 4 : $indent * 2}] "" $pcell_name $count $flat_count]
    }
}

proc dmShapeDump {shape {simple 0} {indent 0}} {
    global dmObject_Rect dmObject_Poly dmObject_Path dmObject_Text dmObject_RectArray dmObject_PolyArray dmObject_PathArray dmObject_TextArray
    if {$shape eq ""} {
        return
    }

    set type [$shape type]
    if {$type == $dmObject_Rect} {
        dmRectDump $shape $simple $indent
    } elseif {$type == $dmObject_Poly} {
        dmPolyDump $shape $simple $indent
    } elseif {$type == $dmObject_Path} {
        dmPathDump $shape $simple $indent
    } elseif {$type == $dmObject_Text} {
        dmTextDump $shape $simple $indent
    } elseif {$type == $dmObject_RectArray} {
        dmRectDump $shape $simple $indent
        dmArrayDump $shape $indent
    } elseif {$type == $dmObject_PolyArray} {
        dmPolyDump $shape $simple $indent
        dmArrayDump $shape $indent
    } elseif {$type == $dmObject_PathArray} {
        dmPathDump $shape $simple $indent
        dmArrayDump $shape $indent
    } elseif {$type == $dmObject_TextArray} {
        dmTextDump $shape $simple $indent
        dmArrayDump $shape $indent
    } else {
        puts "shape type error!"
    }
}

proc dmDump {obj} {
    if [catch {set objObject $obj}] {
        puts "object is not defined"
        return
    }
    set type [$objObject type]
    switch $type {
        $dmObject_Cell { dmCellDump $objObject }
        $dmObject_Layer { dmLayerDump $objObject }
        $dmObject_LayerHeader { dmLayerHeaderDump $objObject }
        $dmObject_InstHeader { dmInstHeaderDump $objObject }
        $dmObject_HeaderMaster { dmHeaderMasterDump $objObject }
        default {
            if {[dmObject_isInst $objObject]} {
                dmInstDump $objObject
            } else {
                dmShapeDump $objObject
            }
        }
    }
}