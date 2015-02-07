Cocos2dxBook
============
####_サンプルゲームの起動_<br>
#####*本書の「Cocos2d-x開発環境の構築」の章をご覧頂いている前提で解説しています。<br>
1.右上の「Download ZIP」からダウンロードし、解凍します。<br>
2.新規にプロジェクト（名前は何でも大丈夫です。）を作成し、リビルドとビルドを行い、<br>
アプリケーションを実行、Helloworldを確認したらアプリケーションを閉じVisual Studioを終了します。<br>
3.解凍した「Cocos2dxBook-master」フォルダ内の「Classes」と「Resources」フォルダを2.のプロジェクト内に<br>
コピー&ペーストします。（全て上書きしてください。）<br>
4.Visual Studioを起動し、2.のプロジェクト内の「ゲーム名.sln」を起動します。<br>
5.「ソリューションエクスプローラー」内の「2.のプロジェクト名」→「Classes」を右クリックして表示される<br>
「追加」→「既存の項目」をクリックします。<br>
![image](tutorial_images/vs_addFiles.jpg)
<a href="url"><img src="https://github.com/athenaeum-school/Cocos2dxBook/tree/develop/tutorial_images/vs_addFiles.jpg" align="left" height="345" width="1050" ></a><br>
6. 2.のプロジェクトの「Classes」フォルダ内のファイルを全て選択し、右下の「追加（A）」をクリックし、追加します。<br>
7.「ソリューションエクスプローラー」内の「win32」→main.cppを開き、<br>
「eglView->setFrameSize(480, 320)」を「eglView->setFrameSize(320, 480)」にします。<br>
8.リビルドとビルドを行いアプリケーションを立ち上げます。<br>
以上でプレイが出来ます。<br>

タイトル：willYard<br>
ジャンル：引っ張りアクションゲーム<br>

開発環境：<br>
windows7 64bit SP1<br>
Visual Studio Community 2013 Update 4<br>
Cocos2d-x v2.2.6<br>
*他の開発環境での動作確認はしておりません。


概要：<br>
敵を全滅させる目的のゲーム。<br>
タイトル画面をタッチすると、プレイ画面に移動。<br>
自ターンと敵ターンが存在し、自ターンに中央に表示される「touch！」イメージをタッチ。<br>
引っ張って、放し、自機をショット。敵NPCに当ててダメージを与える。<br>
その際、ガイド矢印が表示され、ショットする方向を視認出来る<br>
放してから一定時間経過すると、敵ターンになり、ランダムで敵が攻撃。<br>
こちらのHPが0になるか、敵を全滅させるとステージクリア。
リトライボタンとバックボタンが表示され、<br>
リトライはもう一度プレイ、バックはタイトル画面へそれぞれ移動する。<br>

<a href="http://piposozai.blog76.fc2.com/" title="画像素材/ぴぽや" target="_blank">画像素材/ぴぽや</a>  
<a href="http://maoudamashii.jokersounds.com/" title="音楽素材/魔王魂" target="_blank">音楽素材/魔王魂</a>
