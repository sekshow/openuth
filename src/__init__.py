##
# VS Codeで__init__.pyを変更した場合は，
# カーネルを再起動する必要がある．
##

subject_number = 14 # ユーザID
times_number = 1 # 何日目？
exp = True # 計測が初回の場合True

aruduino_no = 'COM5' # Arduinoとの接続ポート

# 収集データ
path_data = '../data'

# 学習モデル
model_name = 'no' + str(subject_number) + 'day1_model.sav'
path_model = '../model/' + model_name

# 閾値
threshold_move = 5 # 小さすぎるジェスチャの除去
threshold_time = 5 # 短すぎるジェスチャの除去

#センサデータ
# columns = ['ax', 'ay', 'az', 'gx', 'gy', 'gz', 'mx', 'my', 'mz'] # IMU のみ
columns = ['ax', 'ay', 'az', 'gx', 'gy', 'gz', 'mx', 'my', 'mz', 'Cap', 'press'] # 静電容量と圧力センサ込み
