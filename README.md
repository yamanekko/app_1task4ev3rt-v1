# EV3RT用mruby yamanekko版用サンプルコード

## これはEV3RT ver 1.0用です。EV3RT β版を使用したい場合は https://github.com/yamanekko/app_1task を使ってください）

EV3上で動作するmrubyのサンプルコードです。
EV3RTのタスクはメインタスクのみです。Rubyのファイル名はmain_task.rbとしてください。
bin/app_1task を使用すればmain_task.rb以外のファイルは必要ありませんが、ご自身でビルドしたい方のためにコードも提供しています。

同梱しているmain_task.rbは、
超音波センサーが30cm以内に障害物を検知している間、LEDが緑色に光り、検出しなくなると消灯します。
executeメソッドの中身を自由に書き換えて使用してください。

## 使い方
https://qiita.com/yamanekko/items/f5f633df005ca7144cca
