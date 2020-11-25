scaling janus
- https://webrtchacks.com/sfu-cascading/
- https://www.meetecho.com/blog/data-channels-broadcasting-with-janus/streaming2/
- https://groups.google.com/forum/#!topic/meetecho-janus/F-VL6L40BPY
- https://github.com/cargomedia/janus-gateway-rtpbroadcast/issues/40

puppeteer

pdfs of highscalability

inspiration: 
https://modernizr.com/
https://www.adamhartwig.co.uk/skills
https://a.singlediv.com/

classify latex symbols hand drawn
http://detexify.kirelabs.org/classify.html

recording pipeline
- mjr files structure
- adding multiple servers in the same dockerfile 
- ffmpeg command explanation - documentation

ffmpeg \
  -i user_103082_x1580919615924_5307647073881312744480102435_17443aa5-ff43-48cd-92c1-0ff177a1aa7f_2834996264104310_7465600798000214_2020-11-23T19:47:09.029Z.webm \
  -i agent_x1580919615924_soujanyaagent2yellowmessengercom_1622448654434787_8845626791975023_2020-11-23T19:47:09.018Z.webm \
  -filter_complex '[0:v]pad=iw*2:ih[int];[int][1:v]overlay=W/2:0[vid]' \
  -map [vid] \
  -c:v vp8 \
  -crf 23 \
  -preset veryfast \
  output.webm
  
  ffmpeg -i user_103082_x1580919615924_5307647073881312744480102435_17443aa5-ff43-48cd-92c1-0ff177a1aa7f_2834996264104310_7465600798000214_2020-11-23T19:47:09.029Z.webm \
           -i agent_x1580919615924_soujanyaagent2yellowmessengercom_1622448654434787_8845626791975023_2020-11-23T19:47:09.018Z.webm \
           -filter_complex hstack output.mp4
