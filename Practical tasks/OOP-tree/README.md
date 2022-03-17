<i><b>eng</i></b>
<h2>Task</h2>
<p>In this paper, it was necessary to build a model of a hierarchical system based on objects.</p>
<p>The first column denotes the parent, the second-the child, 3 - the type of the child object (you can name it in the code, there are 5 of them created, from 2 to 6) and the last is the status of the object (it does not affect anything, but you can always change it)</p>
<p>The exceptions are 1 line (the initial parent) and the last line end true (denotes the end of the tree)</p>
<hr>
<h3>Example of input data</h3>
<br>
root <br>
root obj1 4 1 <br>
root obj2 3 1 <br>
obj1 obj3 5 -1 <br>
obj2 obj4 2 1 <br>
obj4 obj5 3 1 <br>
endtree<br>
 <br>
<hr>
<h3>MAIN EXECUTIVE FILE - main.cpp </h3>
<hr>
<h3>Example of output data</h3>
<br>
Object tree <br>
root<br>
&nbsp;&nbsp;&nbsp;&nbsp;obj1<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj3<br>
&nbsp;&nbsp;&nbsp;&nbsp;obj2<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj4<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj5<br>

<hr><hr>
<i><b>ru</i></b>

<h2>Задача</h2>
<p>В данной работе нужно было построить модель иерархической системы, основанной на объектах.</p>
<p>Первый столбец обозначает родителя, второй - дочерний, 3 - тип дочернего объекта (можно именить его в коде, созданно их 5 штук, от 2 до 6) и последнее статус объекта (ни на что не влияет, но всегда можно это имзменить)</p>
<p>Исключениями являются 1  строка (начальный родитель) и последняя строка endtree (обозначает конец дерева)</p>
<hr>
<h3>ГЛАВНЫЙ ИСПОЛНИТЕЛЬНЫЙ ФАЙЛ - main.cpp</h3>
<hr>
<h3>Пример входных данных</h3>
<br>
root <br>
root obj1 4 1 <br>
root obj2 3 1 <br>
obj1 obj3 5 -1 <br>
obj2 obj4 2 1 <br>
obj4 obj5 3 1 <br>
endtree<br>
 <br>
<hr>
<h3>Пример выходных данных</h3>
<br>
Object tree <br>
root<br>
&nbsp;&nbsp;&nbsp;&nbsp;obj1<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj3<br>
&nbsp;&nbsp;&nbsp;&nbsp;obj2<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj4<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;obj5<br>