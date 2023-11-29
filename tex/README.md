## PDFの生成

github workflowを利用して、コードをまとめたPDFを生成できるようにしています。
github上で、Actionタブ > generate PDF > Run workflowから生成します。

- [gen-pdf.yml](../.github/workflows/gen-pdf.yml) --- github workflowの設定ファイル
- [expander.py](expander.py) --- プログラムをlatexファイルに纏めるためのスクリプト
- [template.tex](template.tex) --- 生成するlatexファイルのプリアンブルなど
- [.latexmkrc](.latexmkrc) --- latexのコンパイルの設定ファイル

## expander.pyについて

プログラムが書かれたファイルをlatexファイルにまとめて印刷がしやすいようにします。
指定されたディレクトリ内で拡張子が`.cpp`, `.hpp`, `.sh`のものが対象です。

### 使い方
```
$ python expander.py -r ../src
```
などで実行してください。

出力ディレクトリ(デフォルトでは`expander.py`が存在するディレクトリに作られる`out`ディレクトリ)内の`main.tex`がコンパイルすべきファイルです。

出力ディレクトリ内にコンパイルに必要なファイルを生成しています。
もしオンラインでコンパイルするときは出力ディレクトリ内のファイルをまとめてアップロードしてください。

### 依存しているパッケージ
日本語対応のため[jlisting](https://ja.osdn.net/projects/mytexpert/downloads/26068/jlisting.sty.bz2)パッケージを利用しています。
https://ymu.dl.osdn.jp/mytexpert/26068/jlisting.sty.bz2 からダウンロードしているので特にセッティングは必要ありません

### オプション

#### 展開するファイルの指定
`expander.py`の後に展開したい`.cpp`, `.hpp`, `.py`, `.sh`ファイルがあるディレクトリを書いてください。
複数のディレクトリの指定もできます。

例：
```
$ python expander.py dir1 dir2
```

#### 出力ディレクトリの指定
`-o`または`--output`フラグで出力ディレクトリを指定できます。

例：
```
$ python expander.py -o outDir dir1
```

#### サブディレクトリまでの探索

`-r`または`--recursive`フラグで指定したディレクトリのサブディレクトリを再帰的に探索させることができます。
逆に**このオプションを指定しなければ再帰的な探索はなされない**ことに注意してください。

例：
```
$ python expander.py -r dir1
```

#### ログの出力
`-l`または`--log`フラグでログの出力を行います。

例：
```
$ python expander.py -l dir1
```
