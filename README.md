# parallelmergesort-delimarr
parallelmergesort-delimarr created by GitHub Classroom

Zuerst werden die Daten in gleiche Teile gleichmässig aufgeteilt. Anzahl Teile = Anzahl Threads.
Dann führt jeder Thread auf seinen Daten sequentiell den Mergesort durch, so sind alle Teile schlussendlich sortiert und müssen nur noch gemerged werden.
Dann werden immer zwei angrenzende Teile gemerged, auch threaded. ZBsp. bei 8 Teilen können gleichzeitig 4 Threads beschäftigt werden. (letzter Schritt des Mergesort)
Wenn alle Teile gemerged sind, ist der ganze Vektor sortiert.
