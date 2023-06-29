MINIRT START 2023.05.31.

<h1 id="table-of-contents"> :book: Table of Contents</h1>
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#lst0"> Scene Examples</a></li>
    <li><a href="#lst1"> Support Operating Systems & Requirements</a></li>
    <li><a href="#lst2"> How to Install & Build </a></li>
    <li><a href="#lst3"> Project Structure Summary </a></li>
    <li><a href="#lst4" > How to implement Viewport </a></li>
    <li><a href="#lst5"> How to implement Objects </a></li>
    <li><a href="#lst6"> How to implement Lights </a></li>
    <li><a href="#lst7"> GUIDE for .rt format </a></li>
    <li><a href="#lst8"> Developers </a></li>
  </ol>
</details>

-------------------------
<br><br><br><br><br><br>






<h1 id="lst0">Scene Examples</h1>

1. scenes/univers.rt

![스크린샷 2023-06-25 오후 6 27 20](https://github.com/minishell-yecseo/miniRT/assets/55090298/898965f1-5ece-443e-b805-9b18e381ed98)

2. scenes/test1.rt

![스크린샷 2023-06-25 오후 6 28 31](https://github.com/minishell-yecseo/miniRT/assets/55090298/83324cdb-0af2-47a9-be70-ffc14e62ac94)

3. scenes/snowman.rt

<img width="1312" alt="Screen Shot 2023-06-29 at 1 14 11 PM" src="https://github.com/minishell-yecseo/miniRT/assets/55090298/d9c7ac29-6d42-4ddc-8445-7977a0d41ed4">

4. scenes/among.rt

<img width="1312" alt="Screen Shot 2023-06-29 at 1 14 27 PM" src="https://github.com/minishell-yecseo/miniRT/assets/55090298/57bbd9f6-6c71-4bdd-a392-675f410e1d83">


-------------------------
<br><br><br><br><br><br>






<h1 id="lst1"> :computer: Support Operating Systems & Requirements</h1>
<h3>1. OS </h3>
<ul>
	  <li><img src="https://img.shields.io/badge/macOS-000000?style=plastic&logo=macOS&logoColor=white"/></li>
</ul>

<h3>2. Requirements </h3>
<ul>
	  <li>MiniLibX : https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html</li>
</ul>

-------------------------
<br><br><br><br><br><br>




<h1 id="lst2">How to Install & Build</h1>

```
$ git clone https://github.com/minishell-yecseo/miniRT
$ cd miniRT
$ make bonus
$ ./miniRT_bonus <TEST.rt>
```

> miniRT_bonus takes only one *.rt file as an input. 
> So, you must write an *.rt file according to the guide below. 
> If the file has error, the program should notice you the number of line of the first error.
 
-------------------------
<br><br><br><br><br><br>





<h1 id="lst3">Project Structure Summary</h1>
<ul>
	<li>Viewport & Camera with Rays</li>
	<li>Objects</li>
	<li>Lights</li>
</ul>

-------------------------
<br><br><br><br><br><br>




<h1 id="lst4">How to implement Viewport</h1>

-------------------------
<br><br><br><br><br><br>



<h1 id="lst5">How to implement Objects</h1>

reference : http://www.illusioncatalyst.com/notes.php

<ul>
	<li>
		<details open="open"><summary>Sphere</summary>
			<img src='https://imgur.com/spy7vz4.png'>
		</details>
	</li>
	<li>
		<details open="open"><summary>Plane</summary>
			<img src='https://imgur.com/EqMu5iN.png'>
		</details>
	</li>
	<li>
		<details open="open"><summary>Cylinder</summary>
			<img src='https://imgur.com/oPHvnFn.png'>
		</details>
	</li>
	<li>
		<details open="open"><summary>Cone</summary>
			<img src='https://imgur.com/koekQfR.png'>
		</details>
	</li>
	<li>
		<details open="open"><summary>Circle</summary>
			<img src='https://imgur.com/IYw6HqF.png'>
		</details>
	</li>
</ul>

-------------------------
<br><br><br><br><br><br>




<h1 id="lst6">How to implement Lights</h1>

-------------------------
<br><br><br><br><br><br>



<h1 id="lst7">GUIDE for .rt format</h1>

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
Surface consists of type and options.

 	[ types ]
      	1) color : takes one option : <color vector>
      	2) checker : takes two options : <color vector> <color vector>
      	3) texture : takes two options : "texture.xpm" "bumpmap.xpm"

[ examples ]

    1) sp       texture      images/test.xpm      images/test2.xpm     0,0,0      5
    2) pl       color        255,25,255           0,0,0                0,1.0,0
    3) co       checker      0,0,0                255,255,255          0,0,0      -0,2,1,0       10     20


-------------------------
<br><br><br><br><br><br>


<h1 id="lst8">Developers</h1>
<h1></h1>

-------------------------
