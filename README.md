<h1>Jerryboree</h1>
<p>A daycare for Jerries from the show "Rick And Morty"</p>
<p>Manage Jerries from different planets and perform operations such as dropping off
a Jerry in the daycare, adding a characteristic to Jerry and more. </p>
<h2>System Architecture</h2>
<p>The system contains four implemented generic ADTs- key value pair, linked list, hash table and multi value hash table, and uses each of them in different contexts in order to improve space complexity and time complexity.</p>
<h2>Usage</h2>
<p> To run the program use: </p>
<pre>./JerryBoree &ltnumberOfPlanets&gt &ltconfigurationFile&gt </pre>
<p>where:</p>
<ul>
<li>numberOfPlanets- the number of planets in the configuration file</li>
<li>configurationFile- the path to the configuration file</li>
</ul>
configuration file format:
<pre>Planets
planetName1,x1,y1,z1
planetName2,x2,y2,z2
Jerries
ID1,dimension1,PlanetName1,happinesLevel
    Characteristic1:value1
    Characteristic2:value2
ID2,dimension2,PlanetName1,happinesLevel</pre>
<p>e.g : </p> 
<pre>Planets
Earth,123.1,8392,99.2
Jerries
23dF21,C-137,Earth,50
	Height:166.2
	LimbsNumber:4
	Weight:80
1q56,C-455,Earth,10</pre>
