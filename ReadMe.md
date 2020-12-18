
# Table of Contents

1.  [About](#orgb729727)
2.  [WX for TWE-Lite MWX](#org2edfc2e)
    1.  [Module List](#org9c57ce2)
    2.  [See](#org5b90f56)


<a id="orgb729727"></a>

# About

Willow eXtension Library (WX) は，組み込みマイコン用の拡張フレームワークです。

WX for MWXは、無線マイコンTWE-Liteのために開発元のモノワイヤレスが開発中のライブラリ"MWX"上で動作します。


<a id="org2edfc2e"></a>

# WX for TWE-Lite MWX


<a id="org9c57ce2"></a>

## Module List

-   Timekeeper: 一定時間経過後、または一定間隔で任意の関数を呼び出すためのモジュール
-   AQM0802: 8x2文字I2C接続LCD(ST7032i搭載)を使用するためのモジュール
-   ATP3011: AquesTalk音声合成LSIをSPI(Mode3)で利用するためのモジュール
-   FIFO: C++のTemplateを使用した可変長リングバッファ
-   SerialPacker:  任意のバイト列からシリアル送信用のパケットを生成するためのモジュール
-   SerialUnpacker: シリアル受信したパケットにエラーチェックを行いバイト列を格納するためのモジュール


<a id="org5b90f56"></a>

## See

以下に示すMWXの制限事項により，一部C++的に好ましくない実装があります．

-   new, new[] 演算子でのメモリ確保は行えますが、確保したメモリを破棄することはできません。
-   グローバルオブジェクトのコンストラクタが呼び出されません。
-   例外 exceptionが使用できません。
-   仮想関数 virtualが使用できません。
