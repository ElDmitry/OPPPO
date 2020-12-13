# Практические работы по ОПППО

### Репозиторий для организации кода практических работ по предмету *Организация процесса проектирования программного обеспечения*.

Каждая практическая работа представляет собой задание, состоящее из нескольких этапов.
В свою очередь, каждое выполненное задание соответствует определенному коммиту.

## Задание
<table>
  <thead>
    <tr>
      <td></td>
      <td></td>
      <th colspan="3" scope="colgroup">Коммиты</th>
    </tr>
    <tr>
      <th scope="col">№</th>
      <th scope="col">Выполняемая работа</th>
      <th scope="col">1 работа</th>
      <th scope="col">2 работа</th>
      <th scope="col">3 работа</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1</td>
      <td>
        <p>Разработка базового варианта программы, программа должна:</p>
        <ul>считать «объекты» из текстового файла в «контейнер»;</ul>
        <ul>вывести содержимое контейнера на экран;</ul>
        <p>Типы объектов и контейнера должны соответствовать варианту,
           выданному преподавателем. Программа обрабатывает 2 типа объ-
           ектов в соответствии с вариантом.
        </p>
        <p>Порядок вывода элементов определяется порядком размещения
           элементов в контейнере. Также выводится порядковый номер эле-
           мента в контейнере и общее количество размещённых элементов.
           Для хеш массива вывод необходимо организовать в виде иерархии.
        </p>
      </td>
      <td><a href="https://github.com/ElDmitry/OPPPO/commit/eada573d8e81aacdc4fbc9775d5e6af40b2e4d4c">eada573</a><br>
          <a href="https://github.com/ElDmitry/OPPPO/commit/5c2807212ad481c8b75b187db1d4a1fbd6010d13">5c28072</a> </td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>2</td>
      <td>Добавление нового типа объекта.</td>
      <td><a href="https://github.com/ElDmitry/OPPPO/commit/810cd0205c94f940dbcda7200b31e8e74e4c8e43">810cd02</a> </td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>3</td>
      <td>Добавление нового свойства во все типы обрабатываемых объектов.</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>4</td>
      <td>Добавление новой функциональности – функции или метода, выполняющего обработку объектов, считываемых с файла.</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>5</td>
      <td>Добавить в контейнер функцию сортировки в соответствии с вариантом.</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>6</td>
      <td>Добавить в контейнер функцию удаления объектов с определенными свойствами.</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
  </tbody>
</table>

## Вариант
<table>
  <thead>
    <tr>
      <th>Обобщенный артефакт, используемый в задании</th>
      <th>Базовые альтернативы (уникальные параметры, задающие отличительные признаки альтернатив)</th>
      <th>Параметры, общие для всех альтернатив</th>
      <th>Тип контейнера</th>
      </tr>
    <tr>
      <td>Плоская геометрическая фигура.</td>
      <td>Круг (целочисленные координата центра окружности, радиус).
          Прямоугольник (дробные координаты левого верхнего и правого нижнего углов).
      </td>
      <td>Цвет фигуры (перечислимый тип) = {красный, оранжевый, желтый, зеленый, 
      голубой, синий, фиолетовый}. Дата последнего редактирования фигуры.
      </td>
      <td>Хеш массив с разрешением конфликтов через дополнительные списки
      для элементов с одинаковым значением ключа.
      </td>
    </tr>
  </thead>
</table>
