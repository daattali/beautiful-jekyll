var main = {
  bigImgEl: null,
  numImgs: null,

  init: function () {
    // // Shorten the navbar after scrolling a little bit down
    // $(window).scroll(function() {
    //     if ($(".navbar").offset().top > 50) {
    //         $(".navbar").addClass("top-nav-short");
    //         $(".navbar-custom .avatar-container").fadeOut(500);
    //     } else {
    //         $(".navbar").removeClass("top-nav-short");
    //         $(".navbar-custom .avatar-container").fadeIn(500);
    //     }
    // });

    // Init smooth scroll
    window.smoothScroll = new SmoothScroll('a[href*="#"]');

    // Init carousel navigation
    function updateNavCarouselPos() {
      if (window.pageYOffset > 50) {
        $(".covi-nav-fixed").css("top", 0);
      } else {
        $(".covi-nav-fixed").css("top", 50 - window.pageYOffset);
      }
    }

    if ($(".covi-nav-carousel").length > 0) {
      $(".covi-nav-carousel").slick({
        arrows: true,
        centerMode: false,
        variableWidth: true,
        infinite: false,
        draggable: true,
        slidesToShow: 10,
        responsive: [
          {
            breakpoint: 480,
            settings: {
              slidesToShow: 3,
            },
          },
          {
            breakpoint: 600,
            settings: {
              slidesToShow: 5,
            },
          },
        ],
      });
      updateNavCarouselPos();
      $(window).scroll(function () {
        updateNavCarouselPos();
      });
    }

    // Init latest post carousel
    if ($(".covi-latest-posts").length > 0) {
      $(".covi-latest-posts").slick({
        arrows: true,
        centerMode: false,
        infinite: true,
        slidesToShow: 1,
        autoplay: true,
        autoplaySpeed: 5000,
        speed: 750,
        dots: true,
      });
    }

    // On mobile, hide the avatar when expanding the navbar menu
    $("#main-navbar").on("show.bs.collapse", function () {
      $(".navbar").addClass("top-nav-expanded");
    });
    $("#main-navbar").on("hidden.bs.collapse", function () {
      $(".navbar").removeClass("top-nav-expanded");
    });

    // On mobile, when clicking on a multi-level navbar menu, show the child links
    $("#main-navbar").on("click", ".navlinks-parent", function (e) {
      var target = e.target;
      $.each($(".navlinks-parent"), function (key, value) {
        if (value == target) {
          $(value).parent().toggleClass("show-children");
        } else {
          $(value).parent().removeClass("show-children");
        }
      });
    });

    // Ensure nested navbar menus are not longer than the menu header
    var menus = $(".navlinks-container");
    if (menus.length > 0) {
      var navbar = $("#main-navbar ul");
      var fakeMenuHtml =
        "<li class='fake-menu' style='display:none;'><a></a></li>";
      navbar.append(fakeMenuHtml);
      var fakeMenu = $(".fake-menu");

      $.each(menus, function (i) {
        var parent = $(menus[i]).find(".navlinks-parent");
        var children = $(menus[i]).find(".navlinks-children a");
        var words = [];
        $.each(children, function (idx, el) {
          words = words.concat($(el).text().trim().split(/\s+/));
        });
        var maxwidth = 0;
        $.each(words, function (id, word) {
          fakeMenu.html("<a>" + word + "</a>");
          var width = fakeMenu.width();
          if (width > maxwidth) {
            maxwidth = width;
          }
        });
        $(menus[i]).css("min-width", maxwidth + "px");
      });

      fakeMenu.remove();
    }

    // init firebase
    main.initFirebase();

    // show the big header image
    main.initImgs();

    // show maps
    main.initMaps();

    // show graphs
    main.initDailyGraphs();

    // get statistics
    main.getStatisticsData();

    // show cases changes heatmap
    main.initHeatmapCasesChanges();
  },

  initFirebase: function () {
    const firebaseConfig = {
      apiKey: "AIzaSyBWAIFZjF-zSB9SymxXULUCz6BcPYacwL4",
      authDomain: "thongtincovid19-4dd12.firebaseapp.com",
      databaseURL: "https://thongtincovid19-4dd12.firebaseio.com",
      projectId: "thongtincovid19-4dd12",
      storageBucket: "thongtincovid19-4dd12.appspot.com",
      messagingSenderId: "751392916473",
      appId: "1:751392916473:web:2aa4202b9354c668ed3328",
    };

    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
  },

  initImgs: function () {
    // If the page was large images to randomly select from, choose an image
    if ($("#header-big-imgs").length > 0) {
      main.bigImgEl = $("#header-big-imgs");
      main.numImgs = main.bigImgEl.attr("data-num-img");

      // 2fc73a3a967e97599c9763d05e564189
      // set an initial image
      var imgInfo = main.getImgInfo();
      var src = imgInfo.src;
      var desc = imgInfo.desc;
      main.setImg(src, desc);

      // For better UX, prefetch the next image so that it will already be loaded when we want to show it
      var getNextImg = function () {
        var imgInfo = main.getImgInfo();
        var src = imgInfo.src;
        var desc = imgInfo.desc;

        var prefetchImg = new Image();
        prefetchImg.src = src;
        // if I want to do something once the image is ready: `prefetchImg.onload = function(){}`

        setTimeout(function () {
          var img = $("<div></div>")
            .addClass("big-img-transition")
            .css("background-image", "url(" + src + ")");
          $(".intro-header.big-img").prepend(img);
          setTimeout(function () {
            img.css("opacity", "1");
          }, 50);

          // after the animation of fading in the new image is done, prefetch the next one
          //img.one("transitioned webkitTransitionEnd oTransitionEnd MSTransitionEnd", function(){
          setTimeout(function () {
            main.setImg(src, desc);
            img.remove();
            getNextImg();
          }, 1000);
          //});
        }, 6000);
      };

      // If there are multiple images, cycle through them
      if (main.numImgs > 1) {
        getNextImg();
      }
    }
  },

  getImgInfo: function () {
    var randNum = Math.floor(Math.random() * main.numImgs + 1);
    var src = main.bigImgEl.attr("data-img-src-" + randNum);
    var desc = main.bigImgEl.attr("data-img-desc-" + randNum);

    return {
      src: src,
      desc: desc,
    };
  },

  setImg: function (src, desc) {
    $(".intro-header.big-img").css("background-image", "url(" + src + ")");
    if (typeof desc !== typeof undefined && desc !== false) {
      $(".img-desc").text(desc).show();
    } else {
      $(".img-desc").hide();
    }
  },

  initMaps: async function () {
    const storage = firebase.storage();
    // JP map overview
    if ($("#map-jp-overview").length > 0) {
      try {
        // load data from firebase storage
        const fileRef = storage.ref("prefecture-by-date.json");
        const url = await fileRef.getDownloadURL().catch((e) => {
          throw e;
        });
        const metadata = await fileRef.getMetadata().catch((e) => {
          throw e;
        });
        const response = await fetch(url).catch((e) => {
          throw e;
        });
        const responseData = await response.json().catch((e) => {
          throw e;
        });

        const data = _.chain(responseData)
          .mapValues((value, key) => {
            return {
              prefecture: value["Tỉnh/Thành phố"],
              value: value["Tổng"],
            };
          })
          .values()
          .value();

        // prepare data to render
        const updatedAt = _.chain(responseData)
          .first()
          .omit(["Tỉnh/Thành phố", "Tổng"])
          .keys()
          .map((d) => moment(`2020/${d}`))
          .max()
          .value();

        // Create the chart
        Highcharts.mapChart("map-jp-overview", {
          chart: {
            map: "countries/jp/jp-all",
            panning: {
              enabled: true,
              type: "xy",
            },
          },
          title: {
            text: "Bản đồ bệnh nhân COVID-19 Nhật Bản",
          },
          subtitle: false,
          mapNavigation: {
            enabled: true,
            buttonOptions: {
              verticalAlign: "bottom",
            },
          },
          colorAxis: {
            min: 1,
            minColor: "rgba(253,243,198,1)",
            maxColor: "rgba(221,76,50,1)",
            labels: {
              format: "{value}",
            },
          },
          series: [
            {
              data: data,
              name: "Số bệnh nhân",
              states: {
                hover: {
                  color: "#BADA55",
                },
              },
              dataLabels: {
                enabled: true,
                format: "{point.name}",
              },
              joinBy: ["name", "prefecture"],
              nullInteraction: true,
            },
            {
              name: "Separators",
              type: "mapline",
              data: Highcharts.geojson(
                Highcharts.maps["countries/jp/jp-all"],
                "mapline"
              ),
              color: "silver",
              nullColor: "silver",
              showInLegend: false,
              enableMouseTracking: false,
            },
          ],
          tooltip: {
            formatter: function (tooltip) {
              if (this.point.isNull) {
                return `<span style="color:#f7f7f7">●</span> <span style="font-size: 10px"> Số bệnh nhân</span><br/>${this.point.name}: <b>0</b>`;
              }
              // If not null, use the default formatter
              return tooltip.defaultFormatter.call(this, tooltip);
            },
          },
        });

        $("#map-jp-overview__footer").html(
          `<small>Thông tin tính đến ngày ${updatedAt.format("DD/MM")}.</small>`
        );
      } catch (error) {
        // TODO: error handler
        console.error(error);
      }
    }
  },

  initDailyGraphs: async function () {
    try {
      const storage = firebase.storage();
      // daily graph
      if ($(".graph-daily").length > 0) {
        // load data from firebase storage
        const fileRef = storage.ref("prefecture-by-date.json");
        const url = await fileRef.getDownloadURL().catch((e) => {
          throw e;
        });
        const metadata = await fileRef.getMetadata().catch((e) => {
          throw e;
        });
        const response = await fetch(url).catch((e) => {
          throw e;
        });
        const responseData = await response.json().catch((e) => {
          throw e;
        });

        renderDailyGraph(responseData, "Tokyo", "graph-daily");
        window[`renderTokyoByWardGraph`]();
        $("#select-pref").change(() => {
          const prefName = $("#select-pref").val();
          renderDailyGraph(
            responseData,
            prefName,
            "graph-daily"
          );
        window[`render${prefName}ByWardGraph`]();
      });

      }
    } catch (error) {
      // TODO: error handler
      console.error(error);
    }
  },

  getStatisticsData: async function () {
    try {
      const storage = firebase.storage();
      // load data from firebase storage
      const fileRef = storage.ref("overall.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const metadata = await fileRef.getMetadata().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      // print out statistics
      $("[data-id='total_cases']").text(
        responseData["total_cases"].toLocaleString()
      );
      $("[data-id='total_cases_changes']").text(
        `(+${responseData["total_cases_changes"].toLocaleString()})`
      );
      $("[data-id='discharged']").text(
        responseData["discharged"].toLocaleString()
      );
      $("[data-id='discharged_changes']").text(
        `(+${responseData["discharged_changes"].toLocaleString()})`
      );
      $("[data-id='death']").text(responseData["death"].toLocaleString());
      $("[data-id='death_changes']").text(
        `(+${responseData["death_changes"].toLocaleString()})`
      );
      $("[data-id='statistics-updated-at']").text(
        `Cập nhật lúc ${moment(metadata.updated).format("HH:mm DD/MM/YYYY")}.`
      );
    } catch (error) {
      // TODO: error handler
      console.error(error);
    }
  },

  initHeatmapCasesChanges: async function () {
    const storage = firebase.storage();

    const HOKKAIDO_TOHOKU = {
      id: "hokkaido_tohoku",
      label: "Hokkaido + Tohoku",
      prefs: [
        "Hokkaido",
        "Aomori",
        "Iwate",
        "Miyagi",
        "Akita",
        "Yamagata",
        "Fukushima",
      ],
    };
    const KANTO_KOSHINETSU = {
      id: "kanto_koshinetsu",
      label: "Kanto + Koshinetsu",
      prefs: [
        "Ibaraki",
        "Tochigi",
        "Gunma",
        "Saitama",
        "Chiba",
        "Tokyo",
        "Kanagawa",
        "Niigata",
        "Yamanashi",
        "Nagano",
      ],
    };
    const TOKAI_HOKURIKU = {
      id: "tokai_hokuriku",
      label: "Tokai + Hokuriku",
      prefs: [
        "Toyama",
        "Ishikawa",
        "Fukui",
        "Gifu",
        "Shizuoka",
        "Aichi",
        "Mie",
      ],
    };
    const KINKI = {
      id: "kinki",
      label: "Kinki",
      prefs: ["Shiga", "Kyoto", "Osaka", "Hyogo", "Nara", "Wakayama"],
    };
    const CHUGOKU = {
      id: "chugoku",
      label: "Chugoku",
      prefs: ["Tottori", "Shimane", "Okayama", "Hiroshima", "Yamaguchi"],
    };
    const SHIKOKU = {
      id: "shikoku",
      label: "Shikoku",
      prefs: ["Tokushima", "Kagawa", "Ehime", "Kochi"],
    };
    const KYUSHU_OKINAWA = {
      id: "kyushu_okinawa",
      label: "Kyushu + Okinawa",
      prefs: [
        "Fukuoka",
        "Saga",
        "Nagasaki",
        "Kumamoto",
        "Oita",
        "Miyazaki",
        "Kagoshima",
        "Okinawa",
      ],
    };

    if ($(".heatmap-cases-changes").length > 0) {
      try {
        // load data from firebase storage
        const fileRef = storage.ref("prefecture-by-date.json");
        const url = await fileRef.getDownloadURL().catch((e) => {
          throw e;
        });
        const metadata = await fileRef.getMetadata().catch((e) => {
          throw e;
        });
        const response = await fetch(url).catch((e) => {
          throw e;
        });
        const responseData = await response.json().catch((e) => {
          throw e;
        });
        const data = _.chain(responseData)
          .mapValues((value, key) => {
            return {
              prefecture: value["Tỉnh/Thành phố"],
              value: _.chain(value).omit(["Tỉnh/Thành phố", "Tổng"]).value(),
            };
          })
          .value();

        // render common legend
        Highcharts.chart("covi-heatmap-legend", {
          chart: {
            type: "heatmap",
            height: 120,
            marginTop: 0,
            marginBottom: 0,
          },
          title: false,
          yAxis: {
            height: 0,
          },
          colorAxis: {
            min: 1,
            max: 50,
            stops: [
              [0, "#eee"],
              [0.25, "#ffcb70"],
              [0.5, "#feaf4b"],
              [0.75, "#fb923d"],
              [1, "#e03131"],
            ],
          },
          legend: {
            layout: "horizontal",
            align: "left",
            verticalAlign: "top",
          },
          tooltip: false,
        });

        renderHeatmap(data, HOKKAIDO_TOHOKU);
        renderHeatmap(data, KANTO_KOSHINETSU);
        renderHeatmap(data, TOKAI_HOKURIKU);
        renderHeatmap(data, KINKI);
        renderHeatmap(data, CHUGOKU);
        renderHeatmap(data, SHIKOKU);
        renderHeatmap(data, KYUSHU_OKINAWA);
      } catch ($error) {
        console.error($error);
      }
    }
  },
};

// 2fc73a3a967e97599c9763d05e564189

document.addEventListener("DOMContentLoaded", main.init);

function renderHeatmap(data, areaObject) {
  const LIMIT = 90;

  // get render data
  const filtered = _.chain(data)
    .filter((d) => _.includes(areaObject.prefs, d.prefecture))
    .value();
  const dates = _.chain(filtered)
    .map("value")
    .first()
    .keys()
    .mapValues((d) => moment(`2020/${d}`).format("DD/M"))
    .values()
    .value();
  let seriesData = [];
  filtered.forEach((f, idx) => {
    const values = _.values(f.value);
    values.forEach((v, k) => {
      seriesData.push([k, idx, v]);
    });
  });

  // render
  Highcharts.chart(`heatmap-cases-changes-${areaObject.id}`, {
    chart: {
      type: "heatmap",
      plotBorderWidth: 1,
      height: areaObject.prefs.length * 20 + 100,
    },
    boost: {
      useGPUTranslations: true,
    },
    title: {
      text: areaObject.label,
      align: "left",
    },
    xAxis: [
      {
        type: "category",
        categories: dates,
        showLastLabel: true,
        startOnTick: true,
        endOnTick: true,
        min: dates.length - 1 - LIMIT,
        max: dates.length - 1,
        tickWidth: 1,
        tickPositions: [
          dates.length - 1 - LIMIT,
          dates.length - 1 - LIMIT + Math.round(LIMIT / 3),
          dates.length - 1 - LIMIT + 2 * Math.round(LIMIT / 3),
          dates.length - 1,
        ],
        labels: {
          autoRotation: false,
        },
      },
      {
        type: "category",
        categories: dates,
        showLastLabel: true,
        startOnTick: true,
        endOnTick: true,
        min: dates.length - 1 - LIMIT,
        max: dates.length - 1,
        tickWidth: 1,
        tickPositions: [
          dates.length - 1 - LIMIT,
          dates.length - 1 - LIMIT + Math.round(LIMIT / 3),
          dates.length - 1 - LIMIT + 2 * Math.round(LIMIT / 3),
          dates.length - 1,
        ],
        labels: {
          autoRotation: false,
        },
        linkedTo: 0,
        opposite: true,
      },
    ],
    yAxis: {
      categories: areaObject.prefs,
      title: null,
      reversed: true,
      tickWidth: 1,
      min: 0,
      max: areaObject.prefs.length - 1,
    },
    colorAxis: {
      min: 1,
      max: 50,
      stops: [
        [0, "#eee"],
        [0.25, "#ffcb70"],
        [0.5, "#feaf4b"],
        [0.75, "#fb923d"],
        [1, "#e03131"],
      ],
    },
    legend: false,
    tooltip: false,
    series: [
      {
        borderWidth: 1,
        borderColor: "#fff",
        data: seriesData,
        tooltip: false,
        turboThreshold: Number.MAX_VALUE,
      },
    ],
  });
}

function renderDailyGraph(responseData, prefName, graphId) {
  const data = _.chain(responseData)
    .filter(["Tỉnh/Thành phố", prefName])
    .first()
    .omit(["Tỉnh/Thành phố", "Tổng"])
    .value();
  Highcharts.chart(graphId, {
    chart: {
      type: "column",
    },
    legend: {
      enabled: false,
    },
    title: {
      text: `Số lượng bệnh nhân mới tại ${prefName} mỗi ngày`,
    },
    subtitle: {
      text: `Nguồn: <a href="https://www3.nhk.or.jp/news/special/coronavirus/" target="_blank">NHK</a> (Số liệu tính đến ${_.last(
        _.keys(data)
      )})`,
    },
    xAxis: {
      categories: _.keys(data),
    },
    yAxis: {
      min: 0,
      title: false,
    },
    plotOptions: {
      column: {
        pointPadding: 0.2,
        borderWidth: 0,
      },
    },
    series: [
      {
        name: "Số bệnh nhân",
        data: _.values(data),
        color: "rgba(255,159,64,1)",
      },
    ],
  });
}

async function renderTokyoByWardGraph() {
  try {
    const storage = firebase.storage();
    // daily graph
    if ($("#graph-byward").length > 0) {
      // load data from firebase storage
      const fileRef = storage.ref("patient-by-city-tokyo.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      const data = _.chain(responseData)
        .filter((d) => d.label != "小計")
        .orderBy("count")
        .reverse()
        .value();

      Highcharts.chart("graph-byward", {
        chart: {
          type: "column",
        },
        legend: {
          enabled: false,
        },
        title: {
          text: `Số bệnh nhân theo quận`,
        },
        subtitle: {
          text: `Nguồn: <a href="https://stopcovid19.metro.tokyo.lg.jp/">Chính quyền thành phố Tokyo</a>`,
        },
        xAxis: {
          categories: _.map(data, "label_vietnamese"),
          min: 0,
          max: 10,
          scrollbar: {
            enabled: true,
            liveRedraw: true,
          },
        },
        yAxis: {
          min: 0,
          max: _.max(_.map(data, "count")),
          title: false,
        },
        plotOptions: {
          column: {
            pointPadding: 0.2,
            borderWidth: 0,
          },
        },
        series: [
          {
            name: "Số bệnh nhân",
            data: _.map(data, "count"),
            color: "rgba(255,159,64,1)",
          },
        ],
      });
    }
  } catch (error) {
    // TODO: error handler
    console.error(error);
  }
}

async function renderOsakaByWardGraph() {
  try {
    const storage = firebase.storage();
    // daily graph
    if ($("#graph-byward").length > 0) {
      // load data from firebase storage
      const fileRef = storage.ref("patient-by-city-osaka.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      const data = _.chain(responseData)
        .groupBy("Location")
        .mapValues((v, k) => {
          return { location: k, count: v.length };
        })
        .values()
        .sortBy("count")
        .reverse()
        .value();

      Highcharts.chart("graph-byward", {
        chart: {
          type: "column",
        },
        legend: {
          enabled: false,
        },
        title: {
          text: `Số bệnh nhân theo quận`,
        },
        subtitle: {
          text: `Nguồn: <a href="https://covid19-osaka.info/">Chính quyền thành phố Osaka</a>`,
        },
        xAxis: {
          categories: _.map(data, "location"),
          min: 0,
          max: 10,
          scrollbar: {
            enabled: true,
            liveRedraw: true,
          },
        },
        yAxis: {
          min: 0,
          max: _.max(_.map(data, "count")),
          title: false,
        },
        plotOptions: {
          column: {
            pointPadding: 0.2,
            borderWidth: 0,
          },
        },
        series: [
          {
            name: "Số bệnh nhân",
            data: _.map(data, "count"),
            color: "rgba(255,159,64,1)",
          },
        ],
      });
    }
  } catch (error) {
    // TODO: error handler
    console.error(error);
  }
}

async function renderSaitamaByWardGraph() {
  try {
    const storage = firebase.storage();
    // daily graph
    if ($("#graph-byward").length > 0) {
      // load data from firebase storage
      const fileRef = storage.ref("patient-by-city-saitama.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      const data = _.chain(responseData)
        .groupBy("Location")
        .mapValues((v, k) => {
          return { location: k, count: v.length };
        })
        .values()
        .sortBy("count")
        .reverse()
        .value();

      Highcharts.chart("graph-byward", {
        chart: {
          type: "column",
        },
        legend: {
          enabled: false,
        },
        title: {
          text: `Số bệnh nhân theo quận`,
        },
        subtitle: {
          text: `Nguồn: <a href="https://saitama.stopcovid19.jp/">Chính quyền thành phố Saitama</a>`,
        },
        xAxis: {
          categories: _.map(data, "location"),
          min: 0,
          max: 10,
          scrollbar: {
            enabled: true,
            liveRedraw: true,
          },
        },
        yAxis: {
          min: 0,
          max: _.max(_.map(data, "count")),
          title: false,
        },
        plotOptions: {
          column: {
            pointPadding: 0.2,
            borderWidth: 0,
          },
        },
        series: [
          {
            name: "Số bệnh nhân",
            data: _.map(data, "count"),
            color: "rgba(255,159,64,1)",
          },
        ],
      });
    }
  } catch (error) {
    // TODO: error handler
    console.error(error);
  }
}

async function renderKanagawaByWardGraph() {
  try {
    const storage = firebase.storage();
    // daily graph
    if ($("#graph-byward").length > 0) {
      // load data from firebase storage
      const fileRef = storage.ref("patient-by-city-kanagawa.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      const data = _.chain(responseData)
        .groupBy("Location")
        .mapValues((v, k) => {
          return { location: k, count: v.length };
        })
        .values()
        .sortBy("count")
        .reverse()
        .value();

      Highcharts.chart("graph-byward", {
        chart: {
          type: "column",
        },
        legend: {
          enabled: false,
        },
        title: {
          text: `Số bệnh nhân theo quận`,
        },
        subtitle: {
          text: `Nguồn: <a href="http://www.pref.kanagawa.jp/osirase/1369/">Chính quyền thành phố Kanagawa</a>`,
        },
        xAxis: {
          categories: _.map(data, "location"),
          min: 0,
          max: 10,
          scrollbar: {
            enabled: true,
            liveRedraw: true,
          },
        },
        yAxis: {
          min: 0,
          max: _.max(_.map(data, "count")),
          title: false,
        },
        plotOptions: {
          column: {
            pointPadding: 0.2,
            borderWidth: 0,
          },
        },
        series: [
          {
            name: "Số bệnh nhân",
            data: _.map(data, "count"),
            color: "rgba(255,159,64,1)",
          },
        ],
      });
    }
  } catch (error) {
    // TODO: error handler
    console.error(error);
  }
}

async function renderChibaByWardGraph() {
  try {
    const storage = firebase.storage();
    // daily graph
    if ($("#graph-byward").length > 0) {
      // load data from firebase storage
      const fileRef = storage.ref("patient-by-city-chiba.json");
      const url = await fileRef.getDownloadURL().catch((e) => {
        throw e;
      });
      const response = await fetch(url).catch((e) => {
        throw e;
      });
      const responseData = await response.json().catch((e) => {
        throw e;
      });

      const data = _.chain(responseData)
        .groupBy("Location")
        .mapValues((v, k) => {
          return { location: k, count: v.length };
        })
        .values()
        .sortBy("count")
        .reverse()
        .value();

      Highcharts.chart("graph-byward", {
        chart: {
          type: "column",
        },
        legend: {
          enabled: false,
        },
        title: {
          text: `Số bệnh nhân theo quận`,
        },
        subtitle: {
          text: `Nguồn: <a href="https://covid19.civictech.chiba.jp/">Chính quyền thành phố Chiba</a>`,
        },
        xAxis: {
          categories: _.map(data, "location"),
          min: 0,
          max: 10,
          scrollbar: {
            enabled: true,
            liveRedraw: true,
          },
        },
        yAxis: {
          min: 0,
          max: _.max(_.map(data, "count")),
          title: false,
        },
        plotOptions: {
          column: {
            pointPadding: 0.2,
            borderWidth: 0,
          },
        },
        series: [
          {
            name: "Số bệnh nhân",
            data: _.map(data, "count"),
            color: "rgba(255,159,64,1)",
          },
        ],
      });
    }
  } catch (error) {
    // TODO: error handler
    console.error(error);
  }
}
