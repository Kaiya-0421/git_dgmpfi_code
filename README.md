# git_dgmpfi_code

Sahara->code　内に卒業研究で使用した任意精度ライブラリMPFIを使用したデータフロー並列化による実行速度(計算速度)の高速化codeがある

・コンパイルは　make ○○ です。
  ロジスティック写像のデータフローグラフを使用したコードなら make log でコンパイル。
  完全2並列可能な演算アプリケーションでデータフローグラフを使用したコードなら make heiretsu_g_divでコンパイル。
  2つとも実行時には第二引数が精度の数値。./実行ファイル名　1024　なら実行ファイルを1024bit幅で演算。
