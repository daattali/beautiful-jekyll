var touchScale = function(seletor, bg) {
    var startX, endX, scale, x1, x2, y1, y2, imgLeft, imgTop, imgWidth, imgHeight,
        one = false, 
        $touch = $(seletor),
        originalWidth = $touch.width(),
        originalHeight = $touch.height(),
        baseScale = parseFloat(originalWidth/originalHeight),
        imgData = [],
        bgTop = parseInt($(bg).css('top'));
    function siteData(name) {
        imgLeft = parseInt(name.css('left'));
        imgTop = parseInt(name.css('top'));
        imgWidth = name.width();
        imgHeight = name.height();
    }
    $(document).on('touchstart touchmove touchend', $(seletor).parent().selector, function(event){
        var $me = $(seletor),
            touch1 = event.originalEvent.targetTouches[0],  // 第一根手指touch事件
            touch2 = event.originalEvent.targetTouches[1],  // 第二根手指touch事件
            fingers = event.originalEvent.touches.length;   // 屏幕上手指数量
        //手指放到屏幕上的时候，还没有进行其他操作
        if (event.type == 'touchstart') {
            if (fingers == 2) {
                // 缩放图片的时候X坐标起始值
                startX = Math.abs(touch1.pageX - touch2.pageX);
                one = false;
            }
            else if (fingers == 1) {
                x1 = touch1.pageX;
                y1 = touch1.pageY;
                one = true;
            }
            siteData($me);
        }
        //手指在屏幕上滑动
        else if (event.type == 'touchmove') {
            if (fingers == 2) {
                // 缩放图片的时候X坐标滑动变化值
                endX = Math.abs(touch1.pageX - touch2.pageX);
                scale = endX - startX;
                $me.css({
                    'width' : originalWidth + scale,
                    'height' : (originalWidth + scale)/baseScale,
                    'left' : imgLeft,
                    'top' : imgTop
                });
                
            }else if (fingers == 1) {
                x2 = touch1.pageX;
                y2 = touch1.pageY;
                if (one) {
                    $me.css({
                        'left' : imgLeft + (x2 - x1),
                        'top' : imgTop + (y2 - y1)
                    });
                }
            }
        }
        //手指移开屏幕
        else if (event.type == 'touchend') {
            // 手指移开后保存图片的宽
            originalWidth = $touch.width(),
            siteData($me);
            imgData = [[imgLeft, imgTop-bgTop, imgWidth, imgHeight],[0, 0, 640, 640]];
        }
    });
    var getData = function(){
        return imgData;
    };
    return {
        imgData : getData
    }
};