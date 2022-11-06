# Paint with layers

This is my project for Lab 2 of Computer Graphics course - University of Science, VNUHCM.

Content:
<ol>
    <li><a href="#desc">Project description</a></li>
    <li><a href="#build">How to run</a></li>
    <li><a href="#demo">Demo</a></li>
</ol>

## 1. Project description
<span id="desc"></span>
The main content of this project is:
- **Draw 2D objects**: Line, Triangle (special triangles), Quadrilateral (Rectangle and Square), Oval (Circle and Ellipse), Regular Polygons, some special shapes like Arrow, Star, and mathematic symbols (Add, Minus, Times, Divide).
- **2D Filling algorithm**: Boundary Fill algorithm and my custom algorithm (using ***point-in-polygon checking***)

The special thing is we can **select** a drawn shape, then fill it with a color. So one of the most important problem to care about is other shapes *obscured* the selected shape, split that shape into many parts (not connected) (like the rectangle in the image below).

<p align="center">
<img src="https://scontent.xx.fbcdn.net/v/t1.15752-9/314417231_1705427176510922_2942540698542799940_n.png?_nc_cat=100&ccb=1-7&_nc_sid=aee45a&_nc_ohc=EO7kXrYTvbwAX97v7M4&_nc_oc=AQmzWO-hBepsj8hCLS7t29InQU4I1C5IKNtb9fmHhVys7MWR0byrH-uh4y3RjwY69Zv-jOL79Drmh10iyks04HkV&_nc_ad=z-m&_nc_cid=0&_nc_ht=scontent.xx&oh=03_AdTRl6v53QyMuVHXXfSC1N6XdR_0_dtYVYRUgnkWaf5JNw&oe=638F7004"/>
</p>

To deal with above problem, this is a summary of my ideas:
- Assign the **layer** value to all drawn shapes and all pixels on the window (for detecting the shape we selected).
- When drawing a shape, we will set the layer of this shape to all pixels inside it.
- To fill a shape with a color, we need to fill its pixels. We just set color to a pixel whose layer value is NOT GREATER than the shape's layer value. Also, we call the Boundary Fill algorithm at all pixels inside the bounding box of that shape (with checking conditions to avoid redundant operations).

Also, I just call Boundary Fill algorithm to fill a shape when we **select a shape and choose a color to fill** (it means the shape is already drawn). For other filling situations (such as first filling when we draw the shape, re-draw the window to update animation,...), I will use my custom filling algorithm (for better time complexity).

## 2. How to run
<span id="build"></span>

## 3. Demo
<span id="demo"></span>