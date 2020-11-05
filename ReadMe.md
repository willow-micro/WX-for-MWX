
# Table of Contents

1.  [About](#orgde1e531)
2.  [WX for TWE-Lite MWX](#orgdd4095b)
    1.  [Module List](#org8da3a5c)
    2.  [See](#orgf32bc7b)


<a id="orgde1e531"></a>

# About

Willow eXtension Library (WX) は，組み込みマイコン用の拡張フレームワークです。


<a id="orgdd4095b"></a>

# WX for TWE-Lite MWX


<a id="org8da3a5c"></a>

## Module List

-   AQM0802: 8x2文字I2C接続LCD(ST7032i)搭載を使用するためのモジュール
-   ATP3011: AquesTalk pico 音声合成LSI(ATP3011)をSPIで利用するためのモジュール
-   FIFO: templateを使用した可変長リングバッファ


<a id="orgf32bc7b"></a>

## See

以下に示すMWXの制限事項により，一部C++的に好ましくない実装があります．

-   new, new[] 演算子でのメモリ確保は行えますが、確保したメモリを破棄することはできません。C++ライブラリで動的メモリ確保をするものは殆どが事実上利用不可能です。一度だけ生成してそれ以降破棄しないオブジェクトに使用しています。
-   グローバルオブジェクトのコンストラクタが呼び出されません。

参考：必要な場合は、初期化関数(setup()) で new ((void\*)&obj\_global) class\_foo(); のように初期化することでコンストラクタの呼び出しを含めた初期化を行えます。

-   例外 exceptionが使用できません。
-   仮想関数 virtualが使用できません。
