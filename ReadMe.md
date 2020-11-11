
# Table of Contents

1.  [About](#org8a11d24)
2.  [WX for TWE-Lite MWX](#orgf88b14f)
    1.  [Module List](#org793a169)
    2.  [See](#org454a7f3)


<a id="org8a11d24"></a>

# About

Willow eXtension Library (WX) は，組み込みマイコン用の拡張フレームワークです。


<a id="orgf88b14f"></a>

# WX for TWE-Lite MWX


<a id="org793a169"></a>

## Module List

-   Timekeeper: 一定時間経過後、または一定間隔で関数を呼び出すためのモジュール
-   AQM0802: 8x2文字I2C接続LCD(ST7032i搭載)を使用するためのモジュール
-   ATP3011: AquesTalk音声合成LSI(ATP3011)をSPIで利用するためのモジュール
-   FIFO: templateを使用した可変長リングバッファ


<a id="org454a7f3"></a>

## See

以下に示すMWXの制限事項により，一部C++的に好ましくない実装があります．

-   new, new[] 演算子でのメモリ確保は行えますが、確保したメモリを破棄することはできません。
-   グローバルオブジェクトのコンストラクタが呼び出されません。
-   例外 exceptionが使用できません。
-   仮想関数 virtualが使用できません。
