## What is this

プログラムが書かれたファイルをlatexファイルにまとめて印刷がしやすいようにします。
指定されたディレクトリ内で拡張子が`.cpp`, `.hpp`, `.sh`のものが対象です。

## 使い方
```
$ python expander.py -r ../src
```
などで実行してください。

出力ディレクトリ(デフォルトでは`./out`)内の`main.tex`がコンパイルすべきファイルです。

出力ディレクトリ内にコンパイルに必要なファイルを生成しています。
もしオンラインでコンパイルするときは出力ディレクトリ内のファイルをまとめてアップロードしてください。

## 依存しているパッケージ
日本語対応のため[plistings](https://github.com/h-kitagawa/plistings)パッケージを利用しています。
直接 https://raw.githubusercontent.com/h-kitagawa/plistings/master/plistings.sty からダウンロードしているので特にセッティングは必要ありません。（TODO リポジトリをpublicにする前にライセンスの表示）

## オプション

### 展開するファイルの指定
`expander.py`の後に展開したい`.cpp`, `.hpp`ファイルがあるディレクトリを書いてください。
複数のディレクトリのしてもできます。

例：
```
$ python expander.py dir1 dir2
```

### 出力ディレクトリの指定
`-o`または`--output`フラグで出力ディレクトリを指定できます。

例：
```
$ python expander.py -o outDir dir1
```

### サブディレクトリまでの探索

`-r`または`--recursive`フラグで指定したディレクトリのサブディレクトリを再帰的に探索させることができます。
逆に**このオプションを指定しなければ再帰的な探索はなされない**ことに注意してください。

例：
```
$ python expander.py -r dir1
```

### ログの出力
`-l`または`--log`フラグでログの出力を行います。

例：
```
$ python expander.py -l dir1
```
