# 使い方（初回）
1. Pythonをインストール（python --versionが利用できるか確認）．
2. Visual Studio Codeにて本プロジェクトを開く．
3. `ターミナル→新しいターミナル`でターミナルを開く．
4. `Python -m venv jupyter`と入力しエンターキーを押す．
5. `Ctrl+Shift+P`にてコマンドパレットを開き，`Python: Select Interpreter`にて``を選択する．
6. インタプリタがアクティブ化されているかはどうかは，右下の`powershell`の部分にカーソルを合わせると出てくるウィンドウの一番下が`python: のアクティブ化された環境　~~hogehoge~~`のようになっているはず．
7. `pip list`とうって，インストールされているパッケージを確認．
8. `python -m pip install jupyter`と打って，jupyterをインストール．
9. その他足らないやつを`python -m pip install ~~~hoge~~~`と打って，インストール．
12. あとは，動かしたいコードを動かすだけ．

# カーネル
ビルドの際は，カーネルが入っているのでそれを選択．場所は以下の場所に入ってる．
```
jupyter/Scripts/python.exe
```
