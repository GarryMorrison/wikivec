# wikivec
Wikivec demonstrates that there is semantic similarity encoded in the link structure of Wikipedia. It turns out that the incomming links to a wikipedia page are similar to other pages which share semantic similarity. Using a similarity measure we can exploit that similarity.

## examples
```
$ ./wikivec-similarity-v2.py knowledge
----------------
wikipage: knowledge
pattern: {10316289, ... , 16621562, 602108}
pattern length: 195
----------------
1   knowledge                          100
2   epistemology                       10.3
3   truth                              7.76
4   reason                             7.67
5   Epistemology                       7.38
6   Empiricism                         6.64
7   wisdom                             6.3
8   reality                            6.19
9   experience                         6.02
10  perception                         5.69
11  mind                               5.64
12  Descartes                          5.48
13  thought                            5.19
14  skill                              5.16
15  understanding                      5.16
16  nature                             5.12
17  Ren_Descartes                      5.04
18  Karl_Popper                        4.99
19  Metaphysics                        4.99
20  Objectivity_(philosophy)           4.94
21  scientific_method                  4.86
22  Rationalism                        4.84
23  Immanuel_Kant                      4.82
24  David_Hume                         4.72
25  Logic                              4.71
26  Theory_of_justification            4.67
27  observation                        4.62
28  Plato                              4.49
29  logical_positivism                 4.49
30  Category:Concepts_in_epistemology  4.48

Enter table row number, or wikipage: 28
----------------
wikipage: Plato
pattern: {16236545, 1003522, ... , 8142845, 9932799}
pattern length: 945
----------------
1   Plato                 100
2   Aristotle             22.46
3   Socrates              18.58
4   Immanuel_Kant         10.13
5   philosophy            9.79
6   Plutarch              9.24
7   Homer                 8.41
8   The_Republic_(Plato)  7.93
9   metaphysics           7.73
10  Cicero                7.7
11  Pythagoras            7.6
12  John_Locke            7.34
13  epistemology          7.32
14  Stoicism              7.22
15  Ancient_Greece        7.1
16  Thomas_Aquinas        6.99
17  Neoplatonism          6.88
18  philosopher           6.69
19  Herodotus             6.56
20  Platonism             6.55
21  Athens                6.4
22  Bertrand_Russell      6.29
23  Aristophanes          6.28
24  David_Hume            6.21
25  Ren_Descartes         6.16
26  Aeschylus             6.11
27  Zeus                  6.1
28  Democritus            6.09
29  Timaeus_(dialogue)    6.07
30  Heraclitus            6.01

Enter table row number, or wikipage: 21
----------------
wikipage: Athens
pattern: {4186115, 6979593, ... , 1941495, 16449535}
pattern length: 1581
----------------
1   Athens                  100
2   Sparta                  16.06
3   Greece                  13.28
4   Achaemenid_Empire       9.65
5   Roman_calendar          8.6
6   Macedon                 8.0
7   Ancient_Greece          7.89
8   Crete                   7.76
9   Corinth                 7.56
10  Peloponnesian_War       7.34
11  Ab_urbe_condita         7.19
12  Plutarch                7.08
13  Thebes,_Greece          7.03
14  Alexander_the_Great     6.97
15  Piraeus                 6.72
16  Cyprus                  6.67
17  Aegean_Sea              6.59
18  Thrace                  6.58
19  Attica                  6.58
20  Thucydides              6.47
21  calendar_era            6.46
22  Istanbul                6.44
23  Plato                   6.4
24  Anno_Domini             6.35
25  Rome                    6.28
26  Thessaloniki            6.06
27  Greeks                  6.0
28  Herodotus               5.94
29  Argos                   5.89
30  Pausanias_(geographer)  5.88

Enter table row number, or wikipage: London
----------------
wikipage: London
pattern: {13631488, 5406723, ..., 13172716, 7471085}
pattern length: 6781
----------------
1   London                   100
2   England                  14.81
3   United_Kingdom           10.8
4   Paris                    8.79
5   New_York_City            6.55
6   BBC                      6.54
7   Wikipedia:Persondata     6.34
8   France                   6.09
9   The_Guardian             5.48
10  World_War_II             5.43
11  Germany                  5.39
12  Scotland                 5.08
13  Australia                4.93
14  Berlin                   4.91
15  Member_of_Parliament     4.75
16  Italy                    4.74
17  World_War_I              4.7
18  Canada                   4.6
19  Manchester               4.41
20  Conservative_Party_(UK)  4.32
21  Edinburgh                4.19
22  Ireland                  4.16
23  Europe                   4.12
24  New_York                 4.07
25  Spain                    3.99
26  Netherlands              3.97
27  Category:Living_people   3.97
28  India                    3.94
29  Rome                     3.92
30  The_Times                3.84

Enter table row number, or wikipage: Cat
----------------
wikipage: Cat
pattern: {4103426, 2599683, ... , 10992377, 191484}
pattern length: 64
----------------
1   Cat         100
2   Dog         15.2
3   Donkey      14.44
4   Goat        13.64
5   Horse       10.24
6   Ferret      8.82
7   Chicken     8.33
8   Rabbit      8.33
9   Cattle      8.03
10  Pig         7.77
11  Elephant    7.37
12  Goldfish    7.25
13  Llama       7.14
14  Mule        7.14
15  Deer        6.86
16  Mouse       6.74
17  Sheep       6.61
18  Guinea_pig  6.58
19  Rat         6.17
20  Fox         5.75
21  Felinae     5.68
22  Weasel      5.63
23  Goose       5.62
24  Alpaca      5.48
25  Lizard      5.19
26  Duck        5.06
27  Squirrel    4.88
28  Red_deer    4.82
29  Whale       4.76
30  Raccoon     4.71

Enter table row number, or wikipage: World_War_II
----------------
wikipage: World_War_II
pattern: {294912, 5406723, ... , 5373949, 6553598}
pattern length: 12589
----------------
1   World_War_II            100
2   World_War_I             17.18
3   Soviet_Union            10.74
4   Nazi_Germany            9.22
5   Germany                 8.81
6   United_Kingdom          7.92
7   France                  7.43
8   United_States_Navy      6.95
9   Cold_War                6.37
10  United_States           6.02
11  United_States_Army      6.01
12  Japan                   5.93
13  New_York_City           5.87
14  Poland                  5.78
15  The_New_York_Times      5.76
16  Allies_of_World_War_II  5.72
17  Italy                   5.63
18  Vietnam_War             5.6
19  American_Civil_War      5.44
20  London                  5.43
21  Russia                  5.28
22  Adolf_Hitler            5.17
23  Wikipedia:Persondata    5.15
24  Great_Depression        5.04
25  Korean_War              4.94
26  Canada                  4.83
27  Netherlands             4.66
28  England                 4.62
29  United_Nations          4.58
30  Europe                  4.43

Enter table row number, or wikipage: Australia
----------------
wikipage: Australia
pattern: {753671, 8814617, ... , 16089084, 9994237}
pattern length: 5613
----------------
1   Australia             100
2   New_Zealand           19.69
3   Canada                12.54
4   United_Kingdom        11.72
5   South_Africa          10.84
6   New_South_Wales       10.33
7   Sydney                10.15
8   India                 9.86
9   Japan                 9.28
10  Brazil                9.04
11  Melbourne             8.03
12  Queensland            7.92
13  Europe                7.59
14  France                7.4
15  Philippines           7.32
16  China                 7.25
17  Indonesia             7.21
18  Germany               7.09
19  Mexico                7.06
20  Netherlands           7.05
21  Italy                 6.89
22  Argentina             6.8
23  Spain                 6.55
24  Singapore             6.51
25  Russia                6.5
26  Malaysia              6.41
27  Victoria_(Australia)  6.28
28  North_America         6.22
29  Chile                 5.93
30  Hong_Kong             5.88
```

## algorithm
Short summary of the algorithm: we find the [outgoing links from wikipedia pages](http://semantic-db.org/wikipedia-sw/), use that to find the incomming links, hash those, and use them as patterns which we compare using a similarity measure. And remarkably it emerges that pages have semantic similarity, that is somehow baked in to the link structure of wikipedia as a whole. Further, we only need a small subset of wikipedia for this to work. The [30k--wikivec.sw](http://semantic-db.org/sw-examples/30k--wikivec.sw) file was constructed from only 30,000 wikipedia pages, resulting in 1,296,086 wikivec learn rules, and the [300k--wikivec.sw](http://semantic-db.org/sw-examples/300k--wikivec.sw) file was constructed from 300,000 wikipedia pages, resulting in 4,272,182 wikivec learn rules.

Longer explanation of the algorithm: first we extract the outgoing link structure of wikipedia pages, and convert that to mumble/sw notation. (see the [Semantic DB project](https://github.com/GarryMorrison/Semantic-DB/))
Let's say page A links to page X, Y and Z, then in sw notation we have:
`links |page A> => |page X> + |page Y> + |page Z>`  
Consider a few more pages:
```
links |page B> => |page Y> + |page P> + |page Q> + |page D> + |page S>
links |page C> => |page Z> + |page Q> + |page A>
links |page D> => |page X> + |page B> + |page N> + |page M>
links |page E> => |page Y> + |page X> + |page S> + |page T> + |page N> + |page M>
```
Noting that our notation has the advantage of being sparse, so we don't need giant matrices to represent the link structure.
Next, find the inverse links. That is, links that are comming into a page:
```
sa: find-inverse[links]

-- show what we now know:
sa: dump

----------------------------------------
 |context> => |context: wikivec algorithm>
previous |context> => |context: global context>

links |page A> => |page X> + |page Y> + |page Z>
inverse-links |page A> => |page C>

links |page B> => |page Y> + |page P> + |page Q> + |page D> + |page S>
inverse-links |page B> => |page D>

links |page C> => |page Z> + |page Q> + |page A>

links |page D> => |page X> + |page B> + |page N> + |page M>
inverse-links |page D> => |page B>

links |page E> => |page Y> + |page X> + |page S> + |page T> + |page N> + |page M>

inverse-links |page X> => |page A> + |page D> + |page E>

inverse-links |page Y> => |page A> + |page B> + |page E>

inverse-links |page Z> => |page A> + |page C>

inverse-links |page P> => |page B>

inverse-links |page Q> => |page B> + |page C>

inverse-links |page S> => |page B> + |page E>

inverse-links |page N> => |page D> + |page E>

inverse-links |page M> => |page D> + |page E>

inverse-links |page T> => |page E>
----------------------------------------
```
Tidy up by hashing the kets in the superpositions:
```
sa: hash-inverse-links |*> #=> ket-hash[6] inverse-links |_self>
sa: map[hash-inverse-links, wikivec] rel-kets[inverse-links]
sa: dump

----------------------------------------
 |context> => |context: wikivec algorithm>
previous |context> => |context: global context>

links |page A> => |page X> + |page Y> + |page Z>
inverse-links |page A> => |page C>
wikivec |page A> => |3fe0fa>

links |page B> => |page Y> + |page P> + |page Q> + |page D> + |page S>
inverse-links |page B> => |page D>
wikivec |page B> => |c065af>

links |page C> => |page Z> + |page Q> + |page A>

links |page D> => |page X> + |page B> + |page N> + |page M>
inverse-links |page D> => |page B>
wikivec |page D> => |46055b>

links |page E> => |page Y> + |page X> + |page S> + |page T> + |page N> + |page M>

inverse-links |page X> => |page A> + |page D> + |page E>
wikivec |page X> => |532631> + |c065af> + |7e957f>

inverse-links |page Y> => |page A> + |page B> + |page E>
wikivec |page Y> => |532631> + |46055b> + |7e957f>

inverse-links |page Z> => |page A> + |page C>
wikivec |page Z> => |532631> + |3fe0fa>

inverse-links |page P> => |page B>
wikivec |page P> => |46055b>

inverse-links |page Q> => |page B> + |page C>
wikivec |page Q> => |46055b> + |3fe0fa>

inverse-links |page S> => |page B> + |page E>
wikivec |page S> => |46055b> + |7e957f>

inverse-links |page N> => |page D> + |page E>
wikivec |page N> => |c065af> + |7e957f>

inverse-links |page M> => |page D> + |page E>
wikivec |page M> => |c065af> + |7e957f>

inverse-links |page T> => |page E>
wikivec |page T> => |7e957f>

hash-inverse-links |*> #=> ket-hash[6] inverse-links |_self>

----------------------------------------
```
Then filter down to only wikivec learn rules and we are left with:
```
wikivec |page A> => |3fe0fa>
wikivec |page B> => |c065af>
wikivec |page D> => |46055b>
wikivec |page X> => |532631> + |c065af> + |7e957f>
wikivec |page Y> => |532631> + |46055b> + |7e957f>
wikivec |page Z> => |532631> + |3fe0fa>
wikivec |page P> => |46055b>
wikivec |page Q> => |46055b> + |3fe0fa>
wikivec |page S> => |46055b> + |7e957f>
wikivec |page N> => |c065af> + |7e957f>
wikivec |page M> => |c065af> + |7e957f>
wikivec |page T> => |7e957f>
```
Which is now exactly the form we need for our wikivec-similarity code. So, how are our page similarities calculated?
We compare the patterns for each page using the similarity measure: `simm(A, B) = |A intersection B| / |A union B|`, and return the top 30 results in a clean table.

## future
 * write a C++ version
 * add the complete steps from wikipedia to links, to usable sw file
 
## related
 * data is here: [30k--wikivec.sw](http://semantic-db.org/sw-examples/30k--wikivec.sw) and [300k--wikivec.sw](http://semantic-db.org/sw-examples/300k--wikivec.sw).
 * the sw file is a data format introduced in my [Semantic DB project](https://github.com/GarryMorrison/Semantic-DB/).
