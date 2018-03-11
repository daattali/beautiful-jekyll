---
layout: post
title: Cài đặt redis trên hệ điều hành OSX
# subtile: Hãy viết code như một Pythonista
image: /img/2018-03-10-Redis/redis.png
tags: [lap-trinh, programming-language,Database]
categories: [Dev-Database]
date: 2018-03-10
---

# Redis
**Redis:** Giới thiệu các khái niệm cơ bản và cài đặt trên OSX

Redis được viết bằng C, là một phần mềm mã nguồn mở được dùng để lưu trữ một cách tạm thời trên bộ nhớ (hay còn gọi là cache data) dưới dạng key-value và giúp truy xuất dữ liệu một cách nhanh chóng. Redis 

Do tốc độ truy xuất dữ liệu vượt trội so với các cơ sở dữ liệu thông thường như MySQL nên redis được sử dụng rất nhiều trong kỹ thuật Caching. 

**Redis** có 3 đặc thù chính mà đặt nó ngoài sự cạnh tranh với cái khác:

- Redis giữ toàn bộ cơ sở dữ liệu của nó trong bộ nhớ.
- Redis có một bộ kiểu dữ liệu dồi dào khi so tới nhiều lưu trữ dữ liệu key-value.
- Redis có thể backup dữ liệu tới bất kỳ số lượng đĩa phụ.

**Lợi Thế Của Redis**

- Nhanh một cách khác thường: Redis rất nhanh có thể thực hiện khoảng 110000 set dữ liệu trên giây, và 81000 get dữ liệu/giây.
- Hổ trợ giàu các kiểu dữ liệu: redis hổ trợ hầu hết các kiểu dữ liệu mà hầu hét các developer đã biết, giống như: list, set, sorted set, hashes. Cho nên dể dàng giải quyết các vấn đề đa dạng bởi vì chúng ta biết vấn đề nào có thể được xử lý tốt hơn với kiểu dữ liệu đó.
- Nhiều công cụ tiện ích: Redis là một công cụ đa tiện ích và có thể được sử dụng trong một số trường hợp sử dụng như bộ nhớ đệm, hàng đợi tin nhắn. Bất kỳ dữ liệu có đời sống ngắn trong ứng dụng của bạn như session, đếm số lượng khám phá web page…
- Các hoạt động là nguyên tử: Tất cả hoạt động của redis là nguyên tử, tức là một đơn vị nhỏ nhất như nguyên tử, do vậy nó bảo đảm rằng nếu có 2 khách hàng đồng thời truy cập server Redis thì sẽ nhận giá trị cập nhật.

# Install redis

```
brew install redis
```

**install log:**
```
--------------------------------------------------

Nguyens-MacBook-Pro:myevn vinh.nguyenquang$ brew install redis
Updating Homebrew...
==> Auto-updated Homebrew!
Updated 2 taps (homebrew/core, caskroom/cask).
==> New Formulae
autopep8        git-sizer       libbi           lzfse           octomap
caffe           go-bindata      libomp          maxwell         python@2
docker-squash   hss             libserialport   mill            skaffold
fastme          icemon          llvm@5          neomutt         stellar-core
==> Updated Formulae
abcde                                    libhttpseverywhere
abcmidi                                  libical
agedu                                    liblwgeom
ammonite-repl                            libmspub
angular-cli                              libphonenumber
ansible                                  libpq
ansible-cmdb                             libpqxx
ansible-lint                             librasterlite
ansifilter                               librealsense
apache-spark                             librsync
app-engine-java                          libsass
app-engine-python                        libspatialite
arangodb                                 libtensorflow
artifactory                              libtrace
asciinema                                libu2f-host
atdtool                                  libunistring
augustus                                 libvirt
automake                                 libwebsockets
aws-sdk-cpp                              linkerd
awscli                                   llvm
azure-cli                                logrotate
bandcamp-dl                              lorem
bartycrouch                              lynis
bazel                                    macvim
bedops                                   magic-wormhole
bench                                    mame
biogeme                                  mapnik
bit                                      mapserver
bitcoin                                  masscan
bmake                                    maven
boost-python3                            memcached
brotli                                   mercurial
buku                                     meson
burp                                     mikutter
caf                                      mitmproxy
cake                                     mkdocs
calabash                                 mmseqs2
cassandra                                molecule
castxml                                  mongo-c-driver
cayley                                   mongo-cxx-driver
cc65                                     mps-youtube
certbot                                  mrboom
certigo                                  mutt
cfitsio                                  mypy
cgal                                     nano
chamber                                  nanopb-generator
charm-tools                              nco
chromedriver                             nghttp2
chronograf                               nicotine-plus
ckan                                     nim
clamav                                   nnn
clojure                                  node
cockatrice                               node-build
conan                                    node@4
conjure-up                               node@6
consul-backinator                        node@8
container-diff                           nodebrew
corebird                                 nq
creduce                                  nspr
crystal-icr                              numpy
crystal-lang                             ocrmypdf
csvkit                                   ode
csvtomd                                  odpi
ctop                                     offlineimap
cvs2svn                                  onetime
dateutils                                opencoarrays
dcos-cli                                 opencv
ddgr                                     opencv@2
diffoscope                               openimageio
diffuse                                  openrtsp
distcc                                   openvpn
django-completion                        osm2pgsql
dnscrypt-proxy                           p11-kit
dnscrypt-wrapper                         paket
docfx                                    pandoc
docker-machine                           pandoc-citeproc
docker-machine-completion                passenger
doctl                                    pastebinit
dovecot                                  percona-toolkit
dropbear                                 pgcli
dub                                      pgformatter
efl                                      pgroonga
elektra                                  picard-tools
elixir                                   pipenv
emacs-clang-complete-async               plank
eralchemy                                pmd
etcd                                     poco
exempi                                   ponysay
faas-cli                                 postgis
fades                                    postgresql
fb-client                                postgresql@9.4
fcl                                      postgresql@9.5
fdroidserver                             postgresql@9.6
feh                                      pre-commit
fetch-crl                                presto
firebase-cli                             proj
flow                                     prometheus
fluent-bit                               protobuf
fluid-synth                              py2cairo
flyway                                   py3cairo
fn                                       pybind11
folly                                    pyenv
fonttools                                pyqt
fuego                                    python
fuse-emulator                            pytouhou
g3log                                    qpdf
gawk                                     qpid-proton
gdal                                     qscintilla2
get-flash-videos                         quicktype
geth                                     rabbitmq
getmail                                  radare2
gifski                                   re2
gimme                                    redex
git-annex                                restic
git-cola                                 rocksdb
git-lfs                                  rom-tools
git-recent                               root
gitbucket                                roswell
glade                                    rtags
glib-openssl                             rtv
gmt                                      rust
gnatsd                                   s-nail
gnome-autoar                             sassc
gnome-recipes                            saxon
gnu-cobol                                sbcl
go-jira                                  sbtenv
gobject-introspection                    scamper
gom                                      scipy
gomplate                                 sdl2
googler                                  sdl2_image
gosu                                     selenium-server-standalone
gradle                                   shfmt
grafana                                  shyaml
grails                                   simgrid
graphene                                 sip
grc                                      skafos
groovy                                   snakemake
grpc                                     snapcraft
grv                                      source-to-image
gsoap                                    sparkey
gst-python                               spatialite-gui
gtk+                                     spatialite-tools
gutenberg                                spigot
gwyddion                                 spin
gxml                                     sqlmap
hana                                     sstp-client
harfbuzz                                 streamlink
hayai                                    subversion
help2man                                 subversion@1.8
heroku                                   svgo
httpd                                    svtplay-dl
httpie                                   swift-protobuf
hugo                                     swiftformat
icoutils                                 syncthing
igv                                      szip
imagemagick                              terminator
imagemagick@6                            terragrunt
influxdb                                 thefuck
iperf3                                   tile38
ipython                                  tippecanoe
ipython@5                                titlecase
isc-dhcp                                 todoman
iso-codes                                tomcat
jbake                                    tor
jenkins                                  traefik
jenkins-job-builder                      twarc
jhipster                                 twine-pypi
jmxtrans                                 twoping
jnettop                                  twtxt
joplin                                   urh
jpeg                                     uwsgi
json-fortran                             vapoursynth
juju                                     vault
juju-wait                                vdirsyncer
jupyter                                  viewvc
just                                     vim
kedge                                    vim@7.4
keepassc                                 vips
kerl                                     vnstat
khal                                     webpack
khard                                    whatmp3
kobalt                                   wireguard-tools
kompose                                  woboq_codebrowser
kontena                                  xdot
kotlin                                   xerces-c
krakend                                  xml-tooling-c
kubernetes-helm                          xonsh
ldc                                      yaml-cpp
lean-cli                                 yarn
lensfun                                  yosys
libdill                                  you-get
libepoxy                                 youtube-dl
libgaiagraphics                          zig
libgeotiff                               zim
libgosu                                  zint
==> Renamed Formulae
php72 -> php
==> Deleted Formulae
llvm@3.8                                 python3

==> Downloading https://homebrew.bintray.com/bottles/redis-4.0.8.high_sierra.bot
######################################################################## 100.0%
==> Pouring redis-4.0.8.high_sierra.bottle.tar.gz
==> Caveats
To have launchd start redis now and restart at login:
  brew services start redis
Or, if you don't want/need a background service you can just run:
  redis-server /usr/local/etc/redis.conf
==> Summary
🍺  /usr/local/Cellar/redis/4.0.8: 13 files, 2.8MB
Nguyens-MacBook-Pro:myevn vinh.nguyenquang$ 
```

Chú ý 2 câu cuối cùng của install log:

```
To have launchd start redis now and restart at login:
  brew services start redis
Or, if you don't want/need a background service you can just run:
  redis-server /usr/local/etc/redis.conf
```

Để start redis, thực hiện lệnh:
```
redis-server /usr/local/etc/redis.conf
```


Kiểm tra phiên bản redis đang cài trên máy:
```
brew info redis
```

Output:
```
Last login: Sun Mar 11 14:20:05 on ttys004
Nguyens-MacBook-Pro:LaunchAgents vinh.nguyenquang$ brew info redis
redis: stable 4.0.8 (bottled), HEAD
Persistent key-value database, with built-in net interface
https://redis.io/
/usr/local/Cellar/redis/4.0.8 (13 files, 2.8MB) *
  Poured from bottle on 2018-03-11 at 14:08:20
From: https://github.com/Homebrew/homebrew-core/blob/master/Formula/redis.rb
==> Options
--with-jemalloc
	Select jemalloc as memory allocator when building Redis
--HEAD
	Install HEAD version
==> Caveats
To have launchd start redis now and restart at login:
  brew services start redis
Or, if you don't want/need a background service you can just run:
  redis-server /usr/local/etc/redis.conf
Nguyens-MacBook-Pro:LaunchAgents vinh.nguyenquang$ 
```

Kiểm tra redis đang hoạt động:
```
redis-cli ping
```

Ouput:
```
Nguyens-MacBook-Pro:myevn vinh.nguyenquang$ redis-cli ping
PONG
```

Kết quả trả về: PONG --> như vậy là service đang chạy


Để stop redis

```
/usr/local/etc/redis.conf
```


# Uninstall redis:

```
brew uninstall redis
rm ~/Library/LaunchAgents/homebrew.mxcl.redis.plist
```


# Sử dụng brew để check/bật/tắt redis:

```
brew services list
```

```
brew services start redis
```


```
brew services stop redis
```


```
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew services list
==> Tapping homebrew/services
Cloning into '/usr/local/Homebrew/Library/Taps/homebrew/homebrew-services'...
remote: Counting objects: 14, done.
remote: Compressing objects: 100% (10/10), done.
remote: Total 14 (delta 0), reused 10 (delta 0), pack-reused 0
Unpacking objects: 100% (14/14), done.
Tapped 0 formulae (43 files, 55.4KB)
Name      Status  User Plist
redis     stopped      
sonarqube stopped      
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew start redis
Error: Unknown command: start
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew services start redis
==> Successfully started `redis` (label: homebrew.mxcl.redis)
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew services list
Name      Status  User             Plist
redis     started vinh.nguyenquang /Users/vinh.nguyenquang/Library/LaunchAgents/homebrew.mxcl.redis.plist
sonarqube stopped                  
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew services stop redis
Stopping `redis`... (might take a while)
==> Successfully stopped `redis` (label: homebrew.mxcl.redis)
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ brew services list
Name      Status  User Plist
redis     stopped      
sonarqube stopped      
Nguyens-MacBook-Pro:etc vinh.nguyenquang$ 
```