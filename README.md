Cocos2dxBook
============
#####本プロジェクトは「Cocos2d-xでC++ゲームデザインパターンを学ぼう: Design For Cocos2d-x」のサンプルです。<br>
各パターンや導入の解説、詳細については書籍をご覧ください。<br>  
<a href="http://www.amazon.co.jp/Cocos2d-x%E3%81%A7C-%E3%82%B2%E3%83%BC%E3%83%A0%E3%83%87%E3%82%B6%E3%82%A4%E3%83%B3%E3%83%91%E3%82%BF%E3%83%BC%E3%83%B3%E3%82%92%E5%AD%A6%E3%81%BC%E3%81%86-Design-For-Cocos2d-x-ebook/dp/B00T9VLWPI/ref=zg_bs_3229700051_2" title="Cocos2d-xでC++ゲームデザインパターンを学ぼう" target="_blank">Cocos2d-xでC++ゲームデザインパターンを学ぼう: Design For Cocos2d-x [Kindle版]</a><br>  
####_サンプルゲームの起動_<br>
___
#####*本書の「Cocos2d-x開発環境の構築」の章をご覧頂いている前提で解説しています。<br>
1.右上の「Download ZIP」からダウンロードし、解凍します。<br>
2.新規にプロジェクト（名前は何でも大丈夫です。）を作成し、リビルドとビルドを行い、<br>
アプリケーションを実行、Helloworldを確認したらアプリケーションを閉じVisual Studioを終了します。<br>
3.解凍した「Cocos2dxBook-master」フォルダ内の「Classes」と「Resources」フォルダを2.のプロジェクト内に<br>
コピー&ペーストします。（全て上書きしてください。）<br>
4.Visual Studioを起動し、2.のプロジェクト内の「ゲーム名.sln」を起動します。<br>
5.「ソリューションエクスプローラー」内の「2.のプロジェクト名」→「Classes」を右クリックして表示される<br>
「追加」→「既存の項目」をクリックします。<br>  
![image](tutorial_images/vs_addFiles.jpg)<br>  
6.2.のプロジェクトの「Classes」フォルダ内のファイルを全て選択し、右下の「追加（A）」をクリックし、追加します。<br>
7.「ソリューションエクスプローラー」内の「win32」→main.cppを開き、<br>
「eglView->setFrameSize(480, 320)」を「eglView->setFrameSize(320, 480)」にします。<br>
8.リビルドとビルドを行いアプリケーションを立ち上げます。<br>
以上でプレイが出来ます。<br>  
*「未解決の外部シンボル '~' が関数 '~' で参照されました。」と表示される場合*<br>
リビルドを行なってみてください。解決しない場合は、一つめの関数'~'の.hの定義を全く同じに書き直してください。<br>  
**正誤表**<br>
___
この度、本書の以下の部分に誤りがありました。<br>
お詫びして、訂正いたします。<br>  
_・Cocos2d-x開発環境の構築_<br>
4.ビルド、実行（windows7）<br>  
誤「ログで確認出来たファイルを変更してください。」<br>
正「mciplayer.h以外のログで確認出来たファイルを変更してください。」<br>  


###サンプルゲーム
___    
タイトル：willYard<br>
ジャンル：引っ張りアクションゲーム<br>  

  <a href="url"><img src="https://github.com/athenaeum-school/Cocos2dxBook/blob/develop/tutorial_images/playImage.jpg" align="center"></a><br>  

  開発環境：<br>
windows7 64bit SP1<br>
Visual Studio Community 2013 Update 4<br>
Cocos2d-x v2.2.6<br>
*他の開発環境での動作確認はしておりません。<br>


概要：<br>
敵を全滅させる目的のゲーム。<br>
タイトル画面をタッチすると、プレイ画面に移動。<br>
自ターンと敵ターンが存在し、自ターンに中央に表示される「touch！」イメージをタッチ。<br>
引っ張って、放し、自機をショット。敵NPCに当ててダメージを与える。<br>
その際、ガイド矢印が表示され、ショットする方向を視認出来る。<br>
放してから一定時間経過すると、敵ターンになり、ランダムで敵が攻撃。<br>
こちらのHPが0になるか、敵を全滅させるとステージクリア。
リトライボタンとバックボタンが表示され、<br>
リトライはもう一度プレイ、バックはタイトル画面へそれぞれ移動する。<br>  
  __デザインパターンサンプル（導入例）__
  ___
  _デザインパターン名のフォルダについて_  
  
  ・各パターン名フォルダ直下のクラスはClasses内と同一のものです。<br>
  （Classesのバックアップとお考えください。）  <br>  
  Apply 適用後  
  Before 適用前  
  の差分です。  
  
  「ComponentPattern」  
  「Queue」  
  「SandBox」  
  
については、Classes内のファイルを「オリジナル」とし、オリジナルに各パターンフォルダ内の  
「Apply」フォルダ内をコピー＆ペーストし、すべて上書きすると、動作します。  
「TypeObject_Apply」に関しては、「オリジナル」から<br>  
 *Enemy <br> 
 *EnemyRatOne  
*EnemyRatTwo<br>
*EnemyVampire  
*EnemyFactory  

の .h .cppを削除してから、「Apply」内をコピー＆ペーストしてください。  
全てゲームの動作は変わりませんが、各パターンを実装しています。<br>  

_サンプルゲームの画像、音楽素材について_<br>
___
下記のサイトから利用しています。
利用規約に関しては、こちらからご確認ください。<br>

<a href="http://piposozai.blog76.fc2.com/" title="画像素材/ぴぽや" target="_blank">画像素材/ぴぽや</a>  
<a href="http://maoudamashii.jokersounds.com/" title="音楽素材/魔王魂" target="_blank">音楽素材/魔王魂</a>
