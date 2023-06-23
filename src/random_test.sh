test=test.txt # テストケースを出力するファイル
while true; do
    python generater.py > $test # テストケースを生成
    rs1=`./main < $test` # コードを実行1
    rs2=`./guchoku< $test` # コードを実行2
    if [[ $rs1 != $rs2 ]]; then
        echo testcase # 無くてもいい
        echo -----------------------
        cat $test
        echo =======================
        echo your code
        echo -----------------------
        echo "$rs1" # 本質
        echo =======================
        echo guchoku
        echo -----------------------
        echo "$rs2" # 本質
        break 1 # 本質
    fi
done
