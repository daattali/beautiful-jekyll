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
  -i agent_x1580919615924_soujanyaagent2yellowmessengercom_6604787091998167_5538356443885566_2020-11-25T06:51:13.743Z.webm \
  -i user_103083_x1580919615924_5307647073881312744480102435_5d56b8d3-d1ec-4aa7-843a-198f42d8950d_8251266513154196_85405238361816_2020-11-25T06:51:13.686Z.webm \
  -filter_complex '[0:v]pad=iw*2:ih[int];[int][1:v]overlay=W/2:0[vid]' \
  -map [vid] \
  -c:v vp8 \
  -crf 23 \
  -preset veryfast \
  output_trial1.webm
  
  ffmpeg  -i \
  agent_x1580919615924_soujanyaagent2yellowmessengercom_6604787091998167_5538356443885566_2020-11-25T07:51:32.161Z.webm \
  -i user_103085_x1580919615924_9471755872245469669282759907_25d56394-3162-4303-a6f8-2601e8f2bfe3_3938466526761501_3899437724071799_2020-11-25T07:55:17.779Z.webm \
            -filter_complex "[0:v]scale=480:640,setsar=1[l];[1:v]scale=480:640,setsar=1[r];[l][r]hstack;[0][1]amix" output_trial2.webm


ffmpeg  -i file1 -i file2 -filter_complex "[0:v]scale=480:640,setsar=1[l];[1:v]scale=480:640,setsar=1[r];[l][r]hstack;[0][1]amix" outputfile

have some ym related work blog posts: voice video calling.
