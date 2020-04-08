# GameTree
Данное приложение предназначено для хранения списка игр в базе данных и отображением их в виде дерева, с удобным доступом к игре.

# Screenshots

![Screen1](https://i.imgur.com/G5FGBFb.png)
![Screen2](https://i.imgur.com/HXBELTI.png)
![Screen3](https://i.imgur.com/JjKB5uW.png)

# Video

[![Video Preview](https://i.imgur.com/ePLxxpi.png)](https://youtu.be/1QiREsI_0BY)

# Known Bugs
1. Иногда при удалении позиции вылетает runtime error. Скорее всего это связанно с тем что у прокси модели и основной модели разные индексы.
2. При клике на подпозиции раскрывается первая ветка и первая ветка в ней. Это тоже связанно с прокси моделью.
3. После запуска игры невозможно сменить язык.
4. TreeView Header не меняет название при смене языка, хотя в файле перевода он есть.

License
----

MIT