MINIRT START 2023.05.31.

BONUS .rt FORMAT GUIDE

1. A, C are same with mandatory part.
2. L 
  - You can make lights more than one up to 1000.
  - color can be specified.
3. Others (Objects)
  - Every objects's line start with two common tokens, <object_type>, <surface_type, options>
  [ object types ]
    1) sp : sphere
    2) pl : plane
    3) cy : cylinder
    4) co : cone
    5) ci : circle

  [ details ]
		[ Sphere ]
			available token numbers : 5, 6
			sp surface center diameter

		[ Plane ]
			available token numbers : 5, 6
			pl surface center norm

		[ Cylinder ]
			available token number : 7, 8
			cy surface bottom_center axis diameter height

		[ Cone ]
			available token number : 7, 8
			co surface bottom_center axis diameter height

		[ Circle ]
			available token number : 7, 8
			ci surface center axis diameter width

[ surface ]
  - Surface consists of type and options.
    [ types ]
      1) color : takes one option : <color vector>
      2) checker : takes two options : <color vector> <color vector>
      3) texture : takes two options : "texture.xpm" "bumpmap.xpm"

[ examples ]
    1) sp       texture      images/test.xpm      images/test2.xpm     0,0,0      5
    3) pl       color        255,25,255           0,0,0                0,1.0,0
    4) co       checker      0,0,0                255,255,255          0,0,0      -0,2,1,0       10     20
