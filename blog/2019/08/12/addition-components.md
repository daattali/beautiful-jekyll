# addition components (#top)

<h3 id="nav"> navigations </h3>

1. [tweaks](#tweaks)
   * [VNC client gets "No matching security types" when connecting to display :0
   * redshift
   * xdg-user-dirs
2. [draving](#draving)
   * GIMP
3. [internet](#internet)
   * Install the Latest Version of Firefox, SeaMonkey, and Thunderbird With Ubuntuzilla Repository
   * Liferea: RSS-агрегатор
   * RetroShare — это программа для приватного обмена файлами, сообщениями, анонимного распространение контента
   * uGet: the #1 Open Source Download Manager app
   * install chromium stable, dev and daily channels
4. [media](#media)
   * Banshee
   * mpv
   * SMPlayer
   * Audacious
   * Byzanz
   * OBS Studio
   * Clementine
   * Selene Media Encoder
   * youtube-dl
5. [office](#office)
   * geany
   * cherrytree
   * copyq
   * LibreOffice
   * MuPDF
   * xbindkeys
   * Diodon clipboard manager
6. [utilities](#utilities)
   * Double Commander
   * Redshift
   * Midnight Commander
   * Sunflower
   * WineHQ
   * VirtualBox
   * BleachBit
   * FreeFileSync
   * Grub Customizer
7. [themes](#themes)

## 1. <strong id="tweaks">[ tweaks ]</strong> <strong>[ ↑ ](#nav)</strong>

### [VNC client gets "No matching security types" when connecting to display :0](https://www.suse.com/support/kb/doc/?id=7015985)

#### Situation

From the menu go to System Tools --> Settings --> Sharing and enable Screen Sharing.  This will run the Vino server which is the program that will allow a VNC connection to display :0 or the system console.

Once enabled Vino listens on port 5900 for a VNC client connection or 5800 for a connection from a browser.  When using vncviewer from a SUSE Linux Enterprise system or using a VNC client such as Tight VNC on Windows the connection will fail with the message, "No matching security types."

#### Resolution

The Vino server included with SUSE Linux Enterprise 12 introduced the TLC encryption method and by default requires encryption from the client.  The vncviewer and Tight VNC clients do not support this encryption so they appropriately fail with the indicated message.

There are two possible solutions for this situation.

1. Use a client that supports the encryption.  On SUSE Linux Enterprise 12 systems there are two supported programs, vinagre and virt-manager.

2. Disable the encryption requirement for the Vino server.  This option is not displayed in the screen sharing setup so it must be modified using the "gsettings" command.  The following command must be run as the user that has enabled screen sharing:

```
gsettings set org.gnome.Vino enabled true
gsettings set org.gnome.Vino require-encryption false
gsettings set org.gnome.Vino notify-on-connect false
gsettings set org.gnome.Vino prompt-enabled false
gsettings set org.gnome.Vino icon-visibility never
```

You can verify that the setting was changed properly by running this command and looking for the "require-encryption" setting:

```
gsettings list-recursively org.gnome.Vino
```

If there is still trouble connecting after modifying this setting restart the system or restart the xdm service by running "rcxdm restart".  This will kill all currently running desktops so be sure nobody is logged in.

---

### [redshift]

~/.config/redshift.conf

```
; Global settings for redshift
[redshift]
; Set the day and night screen temperatures (Neutral is 6500K)
temp-day=5700
temp-night=3500

; Enable/Disable a smooth transition between day and night
; 0 will cause a direct change from day to night screen temperature.
; 1 will gradually increase or decrease the screen temperature.
transition=1

; Set the screen brightness. Default is 1.0.
;brightness=0.9
; It is also possible to use different settings for day and night
; since version 1.8.
;brightness-day=0.7
;brightness-night=0.4
; Set the screen gamma (for all colors, or each color channel
; individually)
gamma=0.8
;gamma=0.8:0.7:0.8
; This can also be set individually for day and night since
; version 1.10.
;gamma-day=0.8:0.7:0.8
;gamma-night=0.6

; Set the location-provider: 'geoclue2' or 'manual'
; type 'redshift -l list' to see possible values.
; The location provider settings are in a different section.
location-provider=manual

; Set the adjustment-method: 'randr', 'vidmode'
; type 'redshift -m list' to see all possible values.
; 'randr' is the preferred method, 'vidmode' is an older API.
; but works in some cases when 'randr' does not.
; The adjustment method settings are in a different section.
adjustment-method=randr

; Configuration of the location-provider:
; type 'redshift -l PROVIDER:help' to see the settings.
; ex: 'redshift -l manual:help'
; Keep in mind that longitudes west of Greenwich (e.g. the Americas)
; are negative numbers.
[manual]
lat=48.1
lon=11.6

; Configuration of the adjustment-method
; type 'redshift -m METHOD:help' to see the settings.
; ex: 'redshift -m randr:help'
; In this example, randr is configured to adjust screen 1.
; Note that the numbering starts from 0, so this is actually the
; second screen. If this option is not specified, Redshift will try
; to adjust _all_ screens.
[randr]
screen=1
```

---

### [xdg-user-dirs](https://www.freedesktop.org/wiki/Software/xdg-user-dirs/ "xdg-user-dirs")

Что, конечно же, соответствует пресловутому стандарту freedesktop.org. Но, по понятным причинам, крайне не удобно при работе в CLI. Зато легко исправляется такой командой:

```
LANG=C xdg­-user-­dirs-­gtk-­update --­­force
```

Вместо LANG=C можно указать LANG=POSIX или LANG=en_US , это одно и то же. И в любом случае за этим последует панель с запросом подтверждения: С ним следует согласиться, предварительно поставив «птицу» в боксике Don't ask methis again , чтобы в дальнейшем избежать повторения вопроса.

---

## 2. <strong id="draving">[ draving ]</strong> <strong>[ ↑ ](#nav)</strong>

### [GIMP](https://www.gimp.org/) (Stable)

![picture alt](https://upload.wikimedia.org/wikipedia/commons/4/45/The_GIMP_icon_-_gnome.svg "Материал из Википедии — свободной энциклопедии")

```
sudo add-apt-repository ppa:otto-kesselgulasch/gimp
sudo apt update
sudo apt install gimp
```

### [GIMP](https://www.gimp.org/) (Unstable)

```
sudo add-apt-repository ppa:otto-kesselgulasch/gimp-edge
sudo apt update
sudo apt install gimp
```

[back to top](#top "back to top")

---

## 3. <strong id="internet">[ internet ]</strong> ***[ ↑ ](#nav)***

### [Install the Latest Version of Firefox, SeaMonkey, and Thunderbird With Ubuntuzilla Repository](https://www.maketecheasier.com/install-latest-version-firefox-ubuntuzilla/)

Gary Sims 20th Jan 2014

Mozilla has a popular set of Internet applications, the most famous of which is Firefox. Also available is an email application called Thunderbird and a all-in-one internet suite (which incorporates Firefox and Thunderbird plus a HTML Editor, an IRC chat program and some web development tools) called Seamonkey. New versions of all these programs are released quite regularly and if you are using Debian or a distro derived from it, e.g. Ubuntu, Linux Mint, Edubuntu, Kubuntu, Lubuntu, Xubuntu etc., there is a convenient repository available which repacks and distributes the latest official Mozilla builds.

The Ubuntuzilla project provides a repository with the latest official versions of Firefox, SeaMonkey, and Thunderbird. The supplied packages contain unmodified official Mozilla release binaries. Using the Ubuntuzilla repository is quite simple and you only need to execute a few commands to get it up and running.

The first step is to add the repository to the list of package sources. The list of sources to be used by apt and the other package management tools is found in /etc/apt/sources.list. To add the Ubuntuzilla repository, without needing to edit the sources.list file use:

```
echo -e "\ndeb http://downloads.sourceforge.net/project/ubuntuzilla/mozilla/apt all main" | sudo tee -a /etc/apt/sources.list > /dev/null
```

To check that the command executed successfully look at the end of the /etc/apt/sources.list file using the tail command:

```
tail /etc/apt/sources.list
```

The last line should be:

```
deb http://downloads.sourceforge.net/project/ubuntuzilla/mozilla/apt all main
```

Next you need to add the repository’s digital signature. This comes in the form of a cryptographic key and enables apt to validate the packages to check that they are genuine. Execute the following command:

```
sudo apt-key adv --recv-keys --keyserver keyserver.ubuntu.com C1289A29
```

Now that the new repository has been added, the package list needs to be re-synchronized to include the packages available from Ubuntuzilla. To do this tell the apt package manager to update:

```
sudo apt update
```

Installing Firefox, SeaMonkey, or Thunderbird

With the repository added, installing the Mozilla program is very easy. To install the latest version of Firefox use:

```
sudo apt install firefox-mozilla-build
```

To install the latest release of Thunderbird use:

```
sudo apt install thunderbird-mozilla-build
```

To get the most recent version of Seamonkey enter:

```
sudo apt install seamonkey-mozilla-build
```

Once a package is installed, it will supersede any version installed previously installed including the versions that come from your distro’s main repositories. However this can mean that you have two versions of Firefox installed, one called Firefox (or possibly Firefox Web Browser) and one called Mozilla Build of Firefox.

You can either choose to ignore the duplicate or remove the distro supplied version, most likely with a command like sudo apt remove firefox (or thunderbird etc). If you do keep both versions installed and the update manager informs you that the distro version has an update available then you can safely carry out the upgrade as the default version will remain the Ubuntuzilla build and that is always going to be the latest official Mozilla build.
Technical details

The way the package installer works is to copy the actual binaries in /opt/firefox (or /opt/thunderbird etc.) and then a link is placed in /usr/bin. The original link in /usr/bin is renamed as /usr/bin/firefox.ubuntu (or /usr/bin/thunderbird.ubuntu etc.).

To remove the Ubuntuzilla versions use the same apt commands except replace install with remove, e.g.

```
sudo apt remove firefox-mozilla-build
```

and so on.

#### Conclusion

Since most of the major Debian derived distributions often can’t upgrade the supplied versions of Firefox, Thunderbird and Seamonkey (due to the large number of libraries and dependencies that would also need to be upgraded), the Ubuntuzilla repository provides a safe way to upgrade to Mozilla’s latest builds. If you do run into any troubles then the Ubuntuzilla project has a fairly active support forum.

---

### [Liferea: RSS-агрегатор](https://lzone.de/liferea/)

![picture alt](https://upload.wikimedia.org/wikipedia/ru/f/fc/Liferea_logo.png "Материал из Википедии — свободной энциклопедии")

![picture alt](https://lzone.de/liferea/images/liferea-title.png "Liferea, the free news aggregator on your Linux desktop")

```
sudo apt update
sudo apt install liferea
```

---

### [RetroShare — это программа для приватного обмена файлами, сообщениями, анонимного распространение контента](http://retroshare.net/)

![picture alt](https://retroshare.readthedocs.io/en/latest/img/retroshare-symbol.png "Logo")

![picture alt](https://retroshare.readthedocs.io/en/latest/img/interface/newsfeed/feed.png "linux-mint-1.10.4-screen")

```
sudo apt-add-repository ppa:retroshare/unstable
sudo apt update
sudo apt install retroshare06
```

[back to top](#top "back to top")

---

### [uGet: the #1 Open Source Download Manager app](http://ugetdm.com/downloads-linux-mint)

![picture alt](http://ugetdm.com/templates/visuex_uget/images/uget-logo.png "Logo")

![picture alt](http://ugetdm.com/images/screens/showcase/linux-mint-1.10.4-screen.gif "linux-mint-1.10.4-screen")

```
sudo add-apt-repository ppa:plushuang-tw/uget-stable
sudo apt update
sudo apt install uget
```

[back to top](#top "back to top")

---

### [install chromium stable, dev and daily channels](http://community.linuxmint.com/tutorial/view/764)

![picture alt](https://upload.wikimedia.org/wikipedia/commons/archive/2/28/20110309125910!Chromium_Logo.svg "Logo")

![picture alt](https://upload.wikimedia.org/wikipedia/commons/3/3c/Chromium.v.27.0.1425.0.openSUSE.png "screenshot")

For the stable channel

```
sudo add-apt-repository ppa:chromium-daily/stable
```

For the dev channel

```
sudo add-apt-repository ppa:chromium-daily/dev
```

For the daily builds channel

```
sudo add-apt-repository ppa:chromium-daily
```

After this you need to update your sources

```
sudo apt update
```

When the sources update is complete you just need to install the chromium-browser package and the desired version will be installed

At last run

```
sudo apt install chromium-browser
```

> #### Решение проблемы с двойными символами в полях ввода:
>
> Проблема решается так: нужно включить в Chrome (а также Chromium) опцию «Использовать системные границы окна и заголовок» («Use system title bar...»).

[back to top](#top "back to top")

---

## 3. <strong id="media">[ media ]</strong> <strong>[ ↑ ](#nav)</strong>

### [Banshee](http://banshee.fm/)

![picture alt](http://banshee.fm/images/header-logo.png "logo")

![picture alt](http://banshee.fm/images/slides/scaled/miroguide-450.png "screenshot")

> Banshee 2.6.1 is included in Ubuntu 13.04 and 13.10.
>
> Ubuntu has a policy of not updating the version of a shipped application, so the version available in the default repository might be old. Note that Canonical modifies our code to take a 75% cut of our Amazon affiliate revenue. If you use Banshee from the community PPA below, 100% of the affiliate revenue will go to GNOME.
> To add the community-run Banshee Team PPA:

```
sudo add-apt-repository ppa:banshee-team/ppa
sudo apt update; sudo apt install banshee
```

---

### [mpv](http://mpv.io/)

![picture alt](https://raw.githubusercontent.com/mpv-player/mpv.io/master/source/images/mpv-logo-128.png "mpv.io")

[launchpad.net](https://launchpad.net/~mc3man/+archive/ubuntu/trusty-media)

[deb-multimedia.org](http://www.deb-multimedia.org/dists/testing/main/binary-amd64/package/mpv)

```
sudo add-apt-repository ppa:mc3man/trusty-media
sudo apt update
sudo apt dist-upgrade
```

[mc3man](https://launchpad.net/~mc3man/+archive/ubuntu/mpv-tests)

```
sudo add-apt-repository ppa:mc3man/mpv-tests
sudo apt update; sudo apt install mpv
```

---

### [SMPlayer](http://smplayer.sourceforge.net/ru/info)

![picture alt](http://smplayer.sourceforge.net/images/free-media-player.png "SMPlayer")

![picture alt](http://smplayer.sourceforge.net/images/screenshots/mainwindow.png "SMPlayer")

```
sudo add-apt-repository ppa:rvm/smplayer
sudo apt update
sudo apt install smplayer smplayer-themes smplayer-skins
```

---

### [Audacious](http://audacious-media-player.org/)

![screenshot](http://audacious-media-player.org/images/3.6-on-win8.png "screenshot")

```
sudo add-apt-repository ppa:nilarimogard/webupd8
sudo apt update
sudo apt install audacious
```

---

### [Byzanz:GitHub](https://github.com/GNOME/byzanz)

[askubuntu.com](http://askubuntu.com/a/123515)

Best software I ever found to record GIF screencasts is Byzanz.

Byzanz is great because it records directly to GIF, the quality and FPS is impressive while maintaining the size of the files to a minimal.

for 11.10 to 13.10:

Unfortunately support has been dropped and you can no longer find any packages for Ubuntu that wont break your system and have missing unsatisfiable dependencies.

Fortunately Debian still maintains the package for Sid and the GIT repository still exists.

If you want to go ahead and install the .deb file from Sid (works in Ubuntu 11.10, just tested, no warranties!), download it from the Debian packages page and install it with `sudo dpkg -i`.

Also, one of our esteemed moderators has ported the Debian package to a PPA making it easier to install, you can add it to your system and install Byzanz by opening a terminal and typing

```
sudo add-apt-repository ppa:fossfreedom/byzanz
sudo apt update && sudo apt install byzanz
```

for 14.04 and above:

Byzanz is now available from the universe repository

```
sudo apt install byzanz
```

When its installed you can run it in a terminal.

This is a small example I did just now in a vbox with

```
byzanz-record --duration=15 --x=200 --y=300 --width=700 --height=400 out.gif
```

[Record Screen as Animated GIF in Ubuntu with Byzanz](https://www.maketecheasier.com/record-screen-as-animated-gif-ubuntu/)

![picture alt](https://maketecheasier-2d0f.kxcdn.com/assets/uploads/2015/02/byzanz-window-gui-specify-duration.png "make-gui")

[back to top](#top "back to top")

---

### [OBS Studio](https://obsproject.com/)

![screenshot](https://obsproject.com/assets/images/studio_mode.png)

Free and open source software for video recording and live streaming. Download and start streaming quickly and easily on Windows, Mac or Linux.

#### Features

* High performance real time video/audio capturing and mixing, with unlimited scenes you can switch between seamlessly via custom transitions.
* Filters for video sources such as image masking, color correction, chroma/color keying, and more.
* Intuitive audio mixer with filter functionality such as noise gate, noise suppression, and gain.
* Powerful and easy to use configuration options. Add new Sources, duplicate existing ones, and adjust their properties effortlessly.
* Improved and streamlined Settings panel for quickly configuring your broadcasts and recordings.
* Both light and dark themes available to fit your preference

#### Ubuntu installation

FFmpeg is required. If you do not have the FFmpeg installed (if you're not sure, then you probably don't have it), you can get it with the following commands:

**For Ubuntu 14.04 LTS, FFmpeg is not officially included so you will need a specific PPA:**

```
sudo add-apt-repository ppa:kirillshkrogalev/ffmpeg-next
sudo apt update && sudo apt install ffmpeg
```

**For Ubuntu 15.04 and following versions, FFmpeg is officially included:**

```
sudo apt install ffmpeg
```

**Then you can install OBS with the following commands:**

```
sudo add-apt-repository ppa:obsproject/obs-studio
sudo apt update && sudo apt install obs-studio
```

[back to top](#top "back to top")

---

### [Clementine](https://www.clementine-player.org/)

![picture alt](https://www.clementine-player.org/images/logo.png "logo")

![picture alt](https://clementine-player.github.io/pages/images/thumbnails/clementine-1.2-1.png "screenshot")

Clementine — кроссплатформенный музыкальный плеер. Он вобрал в себя лучшее от Amarok 1.4, сделав упор на скорость и легкость поиска и воспроизведения вашей музыки

> Вы можете скачать последнюю версию Clementine для Ubuntu из официального PPA репозитория:

```
sudo add-apt-repository ppa:me-davidsansome/clementine
sudo apt update
sudo apt install clementine
```

[back to top](#top "back to top")

---

### [Selene Media Encoder](http://www.teejeetech.in/p/selene-media-encoder.html)

![picture alt](http://3.bp.blogspot.com/-PTb2j2LOI5c/VAXLWNZmj8I/AAAAAAAAC2Y/aRyNaEB_B3g/s1600/selene.png "logo")

![picture alt](http://2.bp.blogspot.com/-UxD9mXgVBVQ/Vp-pl6D8JXI/AAAAAAAADJY/pCHkiNLuGIU/s1600/Preset_051.png "screenshot")

Selene is an audio/video converter for converting files to OGG/OGV/ MKV/MP4/WEBM/OPUS/AAC/FLAC/MP3/WAV formats. It aims to provide a simple GUI for converting files to popular formats along with powerful command-line options for automated/unattended encoding

##### Features:

* Encode videos to MKV/MP4/OGV/WEBM formats.
* Encode music to MP3/AAC/OGG/OPUS/FLAC/WAV formats.
* Option to pause/resume encoding
* Option to run in background and shutdown PC after encoding
* Bash scripts can be written to control the encoding process
* Commandline interface for unattended/automated encoding

```
sudo apt-add-repository -y ppa:teejee2008/ppa
sudo apt update
sudo apt install selene
```

##### dependencies:

###### Required:

```
libgtk-3 libgee2 libjson-glib rsync realpath libav-tools mediainfo libkate-tools
```

###### Optional:

```
vorbis-tools, opus-tools, vpx-tools, x264, lame, mkvtoolnix, ffmpeg2theora, gpac, sox
```

---

### [youtube-dl](https://rg3.github.io/youtube-dl/index.html)

##### error with libass:

```
sudo ln -s libass.so.9 libass.so.5
```

---

[back to top](#top "back to top")

---

## 5. <strong id="office">[ office ]</strong> <strong>[ ↑ ](#nav)</strong>

## office (#office)

### [Geany](http://www.geany.org/Main/HomePage)

![logo](http://wiki.geany.org/lib/tpl/vector/user/logo.png "logo")

![screenshot](https://www.geany.org/uploads/Gallery/geany_main.png "screenshot")

```
sudo add-apt-repository ppa:geany-dev/ppa
sudo apt update
sudo apt install geany geany-common
```

---

### [cherrytree](http://www.giuspen.com/cherrytree/#downl)

![logo](http://www.giuspen.com/icons_softw/cherrytree.png)

![screenshot](http://www.giuspen.com/images/cherrytree-main_window_text.png)

giuspen PPA:

```
sudo add-apt-repository ppa:giuspen/ppa
```

Vincent Cheng PPA:

```
sudo add-apt-repository ppa:vincent-c/cherrytree
```

---

### [copyq](https://github.com/hluk/CopyQ)

![screenshot](https://hluk.github.io/CopyQ/images/logo.png)

![screenshot](https://hluk.github.io/CopyQ/images/application.png)

[GitHub](https://github.com/hluk/CopyQ/releases/latest)

#### Ubuntu

Install and keep CopyQ always up to date by running the following three commands from the terminal:

```
sudo add-apt-repository ppa:hluk/copyq
sudo apt update
sudo apt install copyq
```

---

### [LibreOffice](http://www.libreoffice.org/ "LibreOffice - Free Office Suite - Fun Project - Fantastic People")

![picture alt](https://ru.libreoffice.org/themes/libo/images/logo.png "LibreOffice")

[Как обновить LibreOffice до версии 5.0 в Ubuntu, Linux Mint](http://linux-user.ru/distributivy-linux/programmy-dlya-linux/kak-obnovit-libreoffice-do-versii-5-0-v-ubuntu-linux-mint/)

Для обновления или установки LibreOffice 5.0 в Ubuntu, Linux Mint необходимо выполнить следующее:

Откройте терминал сочетанием клавиш Ctrl+Alt+T и запустите команду, чтобы добавить PPA:
sudo add-apt-repository -y ppa:libreoffice/ppa

```
sudo add-apt-repository -y ppa:libreoffice/ppa
```

Теперь запустите следующие команды для обновления кеша программ и установки нового LibreOffice через добавленный репозиторий PPA:

```
sudo apt update; sudo apt install libreoffice
```

---

### [MuPDF](https://mupdf.com/ "Home page")

![picture alt](http://mupdf.com/mupdf-logo.png "MuPDF")

#### [MuPDF — компактное и быстрое средство просмотра PDF и XPS](http://linux.2baranga.org/2015/06/mupdf-kompaktnoe-i-bystroe-sredstvo-prosm/)

```
sudo add-apt-repository ppa:ubuntuhandbook1/apps
sudo apt update
sudo apt install mupdf mupdf-tools
```

---

### [Diodon clipboard manager](https://launchpad.net/diodon)

![picture alt](https://launchpadlibrarian.net/127060979/Diodon-64x64.png "Aiming to be the best integrated clipboard manager for the Gnome/Unity desktop")

```
sudo add-apt-repository ppa:diodon-team/stable
sudo apt update
sudo apt install diodon
```

---

[back to top](#top "back to top")

---

## 6. <strong id="utilities">[ utilities ]</strong> <strong>[ ↑ ](#nav)</strong>

### [Double Commander](http://doublecmd.sourceforge.net/)

![picture alt](http://doublecmd.sourceforge.net/static_gallery_mirror/images/328_1.png "Double Commander Linux Qt 4")

[Stable](http://software.opensuse.org/download.html?project=home%3AAlexx2000&package=doublecmd-gtk)

[Nightly](https://software.opensuse.org/download.html?project=home%3AAlexx2000%3Adoublecmd-svn&package=doublecmd-gtk)

---

### [Redshift](https://github.com/maoserr/redshiftgui/releases)

![screenshot](http://maoserr.com/projects/redshiftgui/main.png)

---

### [Midnight Commander](https://www.midnight-commander.org/wiki/Binaries)

![picture alt](http://www.midnight-commander.org/chrome/site/MidnightCommander.png "logo")

![picture alt]( https://www.midnight-commander.org/raw-attachment/ticket/2758/mc1.png "screenshot")

```
sudo add-apt-repository "deb http://www.tataranovich.com/debian trusty main"
sudo add-apt-repository "deb-src http://www.tataranovich.com/debian trusty main"
```

Repository is signed with PGP key 76FB442E, fingerprint: 4A49 2741 9308 3320 450B 7E4D 836C C419 76FB 442E.

You can get it from keyserver:

```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 76FB442E
```

#### [Цветовая схема Xoria256 для Midnight Commander](https://m.habrahabr.ru/post/111605/):

![picture alt](https://hsto.org/storage/1e711cc3/8f5eacbb/1bf3f373/5e7b43fa.png "Habrahabr")

```
export TERM="xterm-256color"
```

at the bottom (top, if ineffective) of your ~/.bashrc file

---

### [Sunflower: Twin-panel file manager](http://sunflower-fm.org/)

![picture alt](http://sunflower-fm.org/site/images/favicon.png "logo")

![picture alt](http://sunflower-fm.org/site/gallery/images/5f9b38108c926a6730000f57c81372a8.png "screenshot")

[download deb](http://sunflower-fm.org/download "download")

---

### [WineHQ](https://www.winehq.org/)

![picture alt](https://www.winehq.org/images/winehq_logo_glass.png "WineHQ")

![picture alt](https://appdb.winehq.org/appimage.php?iId=15855 "screenshot")

> If your system is 64 bit, enable 32 bit architecture (if you haven't already):

```
sudo dpkg --add-architecture i386
```

> Add the repository:

```
sudo add-apt-repository ppa:wine/wine-builds
```

> Update packages:

```
sudo apt update
```

> Then install:

```
sudo apt install --install-recommends winehq-devel
```

---

### [VirtualBox](http://download.virtualbox.org/virtualbox/ "VirtualBox")

![screenshot](https://www.virtualbox.org/raw-attachment/wiki/Screenshots/Mint17.1_on_Ubuntu_14.04.png)

##### Debian-based Linux distributions

Add the following line to your /etc/apt/sources.list:

```
deb http://download.virtualbox.org/virtualbox/debian xenial contrib
```

According to your distribution, replace 'xenial' by 'vivid', 'utopic', 'trusty', 'raring', 'quantal', 'precise', 'lucid', 'jessie', 'wheezy', or 'squeeze'.

(Up to version 3.2 the packages were located in the non-free section. Starting with version 4.0 they are located in the contrib section.)

##### You can add these keys with

```
#here for Debian 8 ("Jessie") / Ubuntu 16.04 ("Xenial") and later
sudo apt-key add oracle_vbox_2016.asc
#here for older distributions.
sudo apt-key add oracle_vbox.asc
```

or combine downloading and registering:

```
wget -q https://www.virtualbox.org/download/oracle_vbox_2016.asc -O- | sudo apt-key add -
wget -q https://www.virtualbox.org/download/oracle_vbox.asc -O- | sudo apt-key add -
```

---

### [BleachBit](http://bleachbit.sourceforge.net/ "Bleachbit")

![picture alt](http://bleachbit.sourceforge.net/sites/default/files/zen_classic_logo_0.png "BleachBit")

![picture alt](http://lh4.ggpht.com/_1XYQfEGGEIw/TOH1j8QX5cI/AAAAAAAACyQ/xXkYNv9BjZs/s400/BleachBit-082-Ubuntu1010-Kurdish.png "BleachBit")

[BleachBit программа-чистильщик](http://pingvinus.ru/program/bleachbit), которая предназначена для быстрой и легкой очистки операционной системы от накопившихся, мусорных файлов

---

### [FreeFileSync](https://www.freefilesync.org/ "Synchronize Files and Folders")

![picture alt](https://www.freefilesync.org/images/FreeFileSync.png "Synchronize Files and Folders")

![picture alt](https://www.freefilesync.org/images/screenshots/Ubuntu.png "FreeFileSync on Ubuntu")

FreeFileSync is a free Open Source software that helps you synchronize files and synchronize folders for Windows, Linux and Mac OS X. It is designed to save your time setting up and running backup jobs while having nice visual feedback along the way.

---

### [Grub Customizer](http://help.ubuntu.ru/wiki/grub_customizer)

![picture alt](https://launchpadlibrarian.net/79909401/64x64.png "Grub Customizer")

[launchpad.net](https://launchpad.net/grub-customizer "Grub Customizer")

```
sudo add-apt-repository ppa:danielrichter2007/grub-customizer
sudo apt update
sudo apt install grub-customizer
```

---

[back to top](#top "back to top")

---

## 7. <strong id="themes">[ themes ]</strong> <strong>[ ↑ ](#nav)</strong>

### numixproject

#### [numix-theme](https://github.com/numixproject/numix-icon-theme)

```
sudo add-apt-repository ppa:numix/ppa
sudo apt update && sudo apt install numix-gtk-theme
```

#### [numix-icon-theme](https://github.com/numixproject/numix-icon-theme)

```
sudo add-apt-repository ppa:numix/ppa
sudo apt update
sudo apt install numix-icon-theme
```

#### [numix-icon-theme-circle](https://github.com/numixproject/numix-icon-theme-circle)

```
sudo add-apt-repository ppa:numix/ppa
sudo apt update
sudo apt install numix-icon-theme-circle
```

### snwh.org

#### [paper-icon-theme](https://snwh.org/paper/download)

```
udo add-apt-repository ppa:snwh/pulp
sudo apt update
sudo apt install paper-icon-theme paper-gtk-theme paper-cursor-theme
```

---

#### [faba-icon-theme](http://snwh.org/moka/faba-icon-theme)

```
sudo add-apt-repository ppa:moka/stable
sudo apt update
sudo apt install faba-icon-theme
sudo apt install faba-mono-icons
```

#### [moka-icon-theme](http://snwh.org/moka/moka-icon-theme/)

```
sudo add-apt-repository ppa:moka/stable
sudo apt update
sudo apt install moka-icon-theme
```

### noobslab

#### [EvolvereSuit](https://github.com/franksouza183/EvolvereSuit)

```
sudo add-apt-repository ppa:noobslab/evolvere -y
sudo apt update
sudo apt install evolvere-icon-suite -y
```

#### [Ambiance & Radiance Flat Colors](http://www.ravefinity.com/p/download-ambiance-radiance-flat-colors.html)

![screenshot](http://4.bp.blogspot.com/-r6ZeXm0vG4c/VaV8iIsapSI/AAAAAAAAFbQ/PFDT3Fh0qII/s1600/FlatColorsBanner20152.png "screenshot")

```
sudo add-apt-repository ppa:ravefinity-project/ppa
sudo apt update
sudo apt install ambiance-flat-colors radiance-flat-colors
```

#### [ubuntu-touch-theme-updated-for-ubuntu](http://www.noobslab.com/2015/08/ubuntu-touch-theme-updated-for-ubuntu.html)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install ubuntu-touch-theme
```

#### [stylishdark-theme-with-3-variants](http://www.noobslab.com/2014/12/stylishdark-theme-with-3-variants.html)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install stylishdark-theme
```

#### [libra-is-great-light-gtk-theme](http://www.noobslab.com/2014/12/libra-is-great-light-gtk-theme-for.html)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install libra-theme
```

#### [Ceti theme](http://www.noobslab.com/2015/04/ceti-vertex-are-perfect-themes-for-your.html)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install ceti-theme
```

#### [Vertex theme](http://www.noobslab.com/2015/04/ceti-vertex-are-perfect-themes-for-your.html)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install vertex-theme
```

#### [Candra OS](http://myubuntu.ru/temy/temy-iz-candra-os-dlya-gnome-shell)

```
sudo add-apt-repository ppa:noobslab/themes
sudo apt update
sudo apt install candra-gs-themes
```

#### [AwOken Icons](http://www.noobslab.com/2014/06/awoken-kawoken-icon-sets-are-available.html)

![picture alt](http://2.bp.blogspot.com/-uoxNd0Vz9Bk/UfbjJ8g2ZLI/AAAAAAAAEGc/tS30xgNovRw/s400/awoken_by_alecive-d2pdw32.jpg "screenshot")

```
sudo add-apt-repository ppa:noobslab/icons
sudo apt update
sudo apt install awoken-icon-theme
```

> To customize icons enter following command:

```
awoken-icon-theme-customization
```

### other...

#### [arc-theme](http://software.opensuse.org/download.html?project=home%3AHorst3180&package=arc-theme)

```
sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/Horst3180/xUbuntu_16.04/ /' >> /etc/apt/sources.list.d/arc-theme.list"
sudo apt update
sudo apt install arc-theme
```

> You can add the repository key to apt. Keep in mind that the owner of the key may distribute updates, packages and repositories that your system will trust (more information). To add the key, run:

```
wget http://download.opensuse.org/repositories/home:Horst3180/xUbuntu_16.04/Release.key
sudo apt-key add - < Release.key
```

#### AwOken

```
sudo add-apt-repository ppa:alecive/antigone
sudo apt update
sudo apt install awoken-icon-theme
```

[back to top](#top "back to top")
