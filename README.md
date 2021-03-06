<h1> Проект по биоинформатике. 1-й курс, СПб АУ. </h1>

<div>
<h2> Визуализация графа </h2>
<p>Кластеры - это почти клики. Если граф хорошо нарисовать, то можно оценить количество компонент, на которые уже потом можно будет его разбить каким-нибудь metis-ом. </p>
Проблема: графы слишком сильно-связаны. Без каких-либо эвристик можно уидеть только большой комок ребер. Что можно сделать?
<ul>
  <li> Выкинуть все ребра весом больше константы. </li>
  <li> Сжать вершины по нулевым ребрам </li>
  <li> Ребра с положительным весом рисовать с какой-то вероятностью.</li>
</il>

<h3> Только нулевые и единичные ребра. </h3>
Можно хорошо оценить снизу количество кластеров. Елси оставить ребра весом не больше единицы, то получаются такие картинки:
<img src="http://cs623716.vk.me/v623716154/2bbfc/XrR-V4OIQkQ.jpg" alt="graph1" >
с единичными ребрами.
<p> Тот же граф без единичных ребер:</p>
<img src="http://cs623716.vk.me/v623716154/2bc05/V8CRY3Zu1JM.jpg" alt="graph2">
<h3> Идея сжатия вершин </h3>
<p> Сожмем вершины по нулевым ребрам и теперь рисовать только единичные. Если полученный граф кластеризовать Марковым, то получится такая симпотичная картинка:</p>
<img src="http://cs624420.vk.me/v624420154/32158/EUUd54jvrjI.jpg" alt="graph3">
<h3> Идея рандома </h3>
Ничего интересного не дала.
<h2> Вывод: </h2>
<p>Первые картинки нам дают железные оценки на нижнюю границу количества кластеров. Оценить сверху это количество путем визуализации скорее всего не получится, однако, как мне подсказывает интуиция, рисунки сжатого графа дают некоторого рода медиану, начиная с которой перебором в обе стороны можно найти оптимальное разбиение. </p>
</div>

<div>
<h2> Metis. Кластеризация псевдослучайных графов </h2>
<p>Интересно понять, с какой вероятностью метис найдет кластеры правильно в интересующих нас графах. Для этого будем генерировать случайные графы (схожей с исследуемыми структурой) и смотреть, как хорошо они разбиваются. </p>
<p>Для этого напишим скриптик, который (для заданного количества тестов, вершин в графе, кластеров и вероятности поломки каждого символа) все сделает. </p>
<h3> Базовая концепция </h3>
  <ol>
  <li>Пусть k - количество кластеров. Сгенерируем k срок - базис. </li>
  <li>Потом сделаем n вершин, каждая из которых - строка из базиса с возможными поломками. </li>
  <li>Построим граф. Вес ребра задается количеством несовпадений соответсвующих символов (можно было бы считать редакционное расстояние, но это вроде не то, что нам надо. Или то?). </li>
  <li>Найдем метисом кластеры, сравним с правильным разбиением. </li>
  <li>Повторим все это несколько раз.</li>
  </ol>
<p>Проблема этого решения в том, что строки из базиса скорее всего получатся совершенно разными, а значит, в графе будет мало ребер и его будет просто разбить. </p>
<h3> Результаты </h3>
  <p>Проблема непохожести решена следующим образом: сначала сгенерируем супер-базис. Потом из него случайными поломками сделаем k базисов. Теперь исходные строки будут похожи. </p>

  <p><b>Выяснилось, что metis разбивает граф на кластеры фиксированного размера</b>, что делает нецелесобразным весь этот эксперемент. Чтоб получить хоть какие-то результаты, будем считать, что размеры кластеров равны. </p>
<table>
<caption> 10 тестов на графе из 100 вершин, разбиваемые на 10 кластеров: </caption>
<tr> <td> <b>Среднее расстояние между строками базиса</b> </td> 
     <td> <b>Вероятность поломки одного символа</b> </td>
     <td> <b>Успех</b> </td> <tr>
<tr> <td> 2 - eps </td> 
     <td> 0.001 </td>
     <td> 91% <tr>
<tr> <td> 2.5 - eps </td> 
     <td> 0.001 </td>
     <td> 99% <tr>
<tr> <td> 2 - eps </td> 
     <td> 0.002 </td>
     <td> 84% <tr>
<tr> <td> 2.5 - eps </td> 
     <td> 0.002 </td>
     <td> 95% <tr>
</table>

<p> Результаты получились неплохие. Какой из этого можно сделать вывод? Если бы мы знали размеры кластеров, можно было бы их найти metis-ом с хорошей, прогнозируемой вероятностью. </p>

<p> Код скрипта можно найти в репозитории. </p>
</div>
