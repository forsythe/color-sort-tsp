### Summary
Instead of trying to find the shortest path through a set of points (x, y), this program does it in 3 dimensions, (x, y, z). Furthermore, I visualize each city with (Red=x, Blue=y, Green=z). The values of x, y, and z are between 0 and 255. I use [2-opt](https://en.wikipedia.org/wiki/2-opt) to find a good solution to this TSP problem.

### Demo (500 colors, 2opt)
<a href="http://www.youtube.com/watch?feature=player_embedded&v=UTO_rdMlOIY
" target="_blank"><img src="http://img.youtube.com/vi/UTO_rdMlOIY/0.jpg" 
alt="Sorting 500 colors: traveling salesman visualized " width="500" height="300" border="10" /></a>
![demo](https://i.gyazo.com/dd66042f9d7c7e8d8d2572c6c0f59ed2.gif)


### Customizable options under `defs.h`  
`NUM_COLORS`: Number of colors ("cities" to find a path through)  
`ANIMATE`: Whether or not to animated the sorting process  

Requires SDL2 for graphics. I included all the necessary files along with the .exe to avoid the hassle of installing SDL.
