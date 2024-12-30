
![](https://img.shields.io/badge/9randeza-%F000000.svg?style=for-the-badge&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

# Оболочка
Решение задачи №7 из [contest.msu.uz](https://contest.msu.uz/) 
> Во входном файле задана функция от 3-х переменных вектором своих значений. Найти все 2-местные функции, которые она порождает с помощью операций суперпозиции, переименования переменных,
> и добавления/удаления несущественных переменных (селекторные функции порождаются любой функцией по определению).
> Каждую функцию записать в выходной файл отдельной строкой, предварительно упорядочить строки лексикографически. Количество функций не печатать.
____

## В репозитории имеются:
1. **main.cpp**
   Это программа демонстрирует логическую составляющую решения. Здесь можно отследить за ходом операций.
2. **contetVer.cpp**
   Это полностью готовая программа которую можно загрузить на контест.
### Разьеснение логики кода:
Основная суть алгоритма заключается в том, что пусть у нас есть функция от трех f(x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>). Сначало подставляем в нее всевозможные комбинации селекторов (простыми словами векторы *0011* *0101*), полученые функции в перемешку с селекторами вновь прогоняем через все комбинации и на i шаге получем множество G<sub>i</sub>, тогда если на i+1 шаге  G<sub>i</sub> = G<sub>i+1</sub> - то G<sub>i</sub> наш ответ.
