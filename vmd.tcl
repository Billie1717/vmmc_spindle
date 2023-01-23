light 0 on
light 1 on
light 2 off
light 3 off
axes location off
stage location off
display projection orthographic
mol modstyle 0 0 VDW 1 30
set sel [atomselect top "name X"]
atomselect0 set radius 0.5
color Name X blue
display depthcue off
set minx 0
set maxx 29.6931
set miny 0
set maxy 29.6931
set minz 0
set maxz 29.6931
draw materials off
draw color white
draw line "$minx $miny $minz" "$maxx $miny $minz"
draw line "$minx $miny $minz" "$minx $maxy $minz"
draw line "$minx $miny $minz" "$minx $miny $maxz"
draw line "$maxx $miny $minz" "$maxx $maxy $minz"
draw line "$maxx $miny $minz" "$maxx $miny $maxz"
draw line "$minx $maxy $minz" "$maxx $maxy $minz"
draw line "$minx $maxy $minz" "$minx $maxy $maxz"
draw line "$minx $miny $maxz" "$maxx $miny $maxz"
draw line "$minx $miny $maxz" "$minx $maxy $maxz"
draw line "$maxx $maxy $maxz" "$maxx $maxy $minz"
draw line "$maxx $maxy $maxz" "$minx $maxy $maxz"
draw line "$maxx $maxy $maxz" "$maxx $miny $maxz"
rotate x by -60
rotate y by -30
rotate z by -15
