window.addEventListener('load', function() {


    var ul = document.querySelector('.tt');
    for (var i = 0; i < ul.children.length; i++) {
        var li = ul.children[i];
        li.setAttribute('index', i);

        li.addEventListener('click', function() {
            // 干掉所有人 把所有的小li 清除 current 类名
            k.className = '';
            for (var i = 0; i < ul.children.length; i++) {
                var q = ul.children[i].querySelector('i');
                q.className = '';
            }
            var p = this.querySelector('i');
            p.className = 'poi1';
            var index = this.getAttribute('index');
            // console.log(index);
            var m = index * 300;
            var body = document.querySelector('body');
            // body.style.transform = 'translateY(' + m + 'px)';
            // console.log(m);
            window.scroll(0, m + 300);
        })
    }


    var k = document.querySelector('#qq');
    var j = document.querySelector('.pp');
    j.addEventListener('click', function() {
        k.className = 'poi';
        for (var i = 0; i < ul.children.length; i++) {
            var q = ul.children[i].querySelector('i');
            q.className = '';
        }
        window.scroll(0, 0);
    })


    var dig = document.querySelector('.dig')
    document.addEventListener('scroll', function() {
        // window.pageYOffset 页面被卷去的头部
        // console.log(window.pageYOffset);
        if (window.pageYOffset >= 480) {
            dig.style.position = 'fixed';
            dig.style.top = '-480px';
        } else {
            dig.style.position = 'absolute';
            dig.style.top = '0'
        }
        var t = Math.floor(window.pageYOffset / 300);
        var h = 1;
        console.log(t - 1);
        if (t < 1) {
            for (var i = 0; i < ul.children.length; i++) {
                var q = ul.children[i].querySelector('i');
                q.className = '';
            }
            k.className = 'poi';
        } else if (t >= 1 && t < 8) {
            for (var i = 0; i < ul.children.length; i++) {
                var q = ul.children[i].querySelector('i');
                q.className = '';
                var index = ul.children[i].getAttribute('index');
                // console.log(index);
                console.log(t - 1);
                if (index == t - 1) {
                    q.className = 'poi1';
                    // console.log(index);
                    // console.log(t);
                }
            }

            k.className = '';

        }
    })



})