rm -f sensor_pipe
mkfifo sensor_pipe
echo "Để gửi dữ liệu ADC,mở Terminal: echo 900 > sensor_pipe"
