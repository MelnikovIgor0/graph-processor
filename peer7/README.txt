Привет! Тут описаны формат корректных входных данных и особенности реализации пира.
1) Корректные способы ввода графа:
1.0) Во всех случаях при вводе разделение нескольких чисел в одной строке осуществляется с помощью
ровно одного пробела, перевод строки осуществляется с помощью символа, соответствующего вашей ОС.
1.1) Для ввода матрицы смежности нужно написать "am" (без кавычек). После этого на следующей 
строке нужно написать целое число n >= 1 и n <= 100, потом, с новой строки начать вводить n^2 чисел,
в n строк, в каждой по n символов, каждое введенное число - 0 или 1 (для i строки j числа 0 если нет 
дуги (ребра) из i в j, 1 если есть). Пример корректного ввода:
====================Ввод графа в виде матрицы смежности========================
am
4
0 1 0 1 
0 0 1 1 
0 1 0 0 
1 0 1 0 
===============================================================================
1.2) Для ввода матрицы инцидентности нужно написать "im", потом на следующей строке нужно ввести 2
натуральных числа: количество вершин (n >= 1 & n <= 100) и количество ребер (m) в графе. После этого нужно
ввести n строк, в каждой по m чисел. Каждое из чисел это -1, 0 или 1 (1 начало ребра, -1 - конец
ребра (для ориентированного графа). Пример корректного ввода:
====================Ввод графа в виде матрицы инцидентности====================
im
4 5
1 1 0 0 0 
-1 0 1 1 0 
0 0 1 0 -1 
0 1 0 -1 1 
===============================================================================
1.3) Для ввода списка смежности нужно написать "al", потом на следующей строке ввести число вершин (n),
далее нужно ввести n строк. Каждая строка начинается с натурального числа k, далее идет k чисел,
вершины, в которые идет ребро из данной. Нумерация вершин идет с 1. Если из вершины исходит 0 ребер,
то нужно написать в строке соответствующей данной вершине 0. Пример корректного ввода:
===================Ввод графа в виде списка смежности==========================
al
4
2 2 4 
2 3 4 
1 2 
2 1 3 
===============================================================================
1.4) Для ввода списка ребер нужно написать "el", потом на следующей строке написать число вершин (n) и
число ребер (m) в графе. После этого нужно ввести m пар натуральных чисел (каждое число от 1 до n),
пара "a b" говорит о том, что есть ребро из a в b. То есть если нужно указать ребро неориентированного
графа (a, b), то нужно указать при вводе списка смежности 2 пары: a b и b a. Пример корректного ввода:
===================Ввод графа в виде списка ребер==============================
el
4 7
1 2
1 4
2 3
2 4
3 2
4 1
4 3
===============================================================================
1.5) На вводимые графы наложены следующие ограничения: в графе должно быть от 1 до 100 вершин, граф
не должен содержать петель, мультиребер, мультипетель, граф должен быть невзвешенным. Также не
гарантируется, что один и тот же граф при представлении в одной и той же форме будет отображен
одинаково (например, для матрицы инцидентности может быть разный порядок отображения ребер; порядок
ребер в списке ребер тоже может отличаться). Если в графе n вершин, то во всех местах, где вводится
номер вершины должно быть введено целое число от 1 до n.
1.6) О вводе графа из файла. Для порректной работы ввода из файла необходимо, чтобы файл с графом
лежал в папке \cmake-build-debug . Для ввода укажите имя файла. Ограничение: имя файла должно состоять
только из английских букв в верхнем и нижнем регистре, также допустимы цифры, точки и нижние
подчеркивания. Кодировка файла UTF8.
2) Корректные способы вывода графа: вывод графа в каком-либо виде соответствует вводу графа в таком же
виде.
3) Взаимодействие с программой:
пользователю доступны следующие команды:
	a) конвертирование. Команда имеет вид "convert <input_stream> <?graph> <output_stream> <output_type>",
	где <input_stream> console если граф вводится с консоли или путь к файлу, откуда считывается граф.
	Если граф вводится из консоли, то его нужно ввести в консоль, если из файла то этот пункт опускается.
	output_stream - куда нужно вывести граф: console если в консоль, путь к файлу в противном случае.
	output_type - строка "am", "im", "al", "el", в соответствии со способом, в котором нужно вывести граф.
	b) получение степеней вершин. Команда имеет вид "degrees <input_stream> <?graph>".
	Входной поток и граф так же как в предыдущем пункте.
	c) получение количества ребер в графе. Команда имеет вид "edges <input_stream> <?graph>".
	По аналогии с предыдущим пунктом.
	d) вывод порядка обхода dfs. Команда имеет вид "dfs <input_stream> ?<graph>".
	e) вывод порядка обхода bfs. Команда имеет вид "bfs <input_stream> ?<graph>".
	f) завепшение работы программы. exit.