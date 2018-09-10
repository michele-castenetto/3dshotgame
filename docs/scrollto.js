;(function(root, factory) {
    if (typeof define === 'function' && define.amd) {
        define([], factory);
    } else if (typeof exports === 'object') {
        module.exports = factory();
    } else {
        root.UTILS = factory();
    }
}(this, function() {


var Animation = (function() {

    var Animation = function(animationFn) {
        this._runLoop = false;
        this._animationFn = animationFn;
    };

    var _runFrame = function() {
        var _this = this;
        if (!this._runLoop) { return; }
        requestAnimationFrame( function() { _runFrame.apply(_this); } );
        this._animationFn();
    };

    Animation.prototype.runFrame = function() {
        return _runFrame.bind(this);
    };

    Animation.prototype.start = function() {
        this._runLoop = true;
        _runFrame.apply(this);
    };

    Animation.prototype.stop = function() {
        this._runLoop = false;
    };

    return Animation;

})();



var scrollto = (function() {
    

    var easings = {
        linear: function(t) {
            return t;
        },
        easeInQuad: function(t) {
            return t * t;
        },
        easeOutQuad: function(t) {
            return t * (2 - t);
        },
        easeInOutQuad: function(t) {
            return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
        },
        easeInCubic: function(t) {
            return t * t * t;
        },
        easeOutCubic: function(t) {
            return (--t) * t * t + 1;
        },
        easeInOutCubic: function(t) {
            return t < 0.5 ? 4 * t * t * t : (t - 1) * (2 * t - 2) * (2 * t - 2) + 1;
        },
        easeInQuart: function(t) {
            return t * t * t * t;
        },
        easeOutQuart: function(t) {
            return 1 - (--t) * t * t * t;
        },
        easeInOutQuart: function(t) {
            return t < 0.5 ? 8 * t * t * t * t : 1 - 8 * (--t) * t * t * t;
        },
        easeInQuint: function(t) {
            return t * t * t * t * t;
        },
        easeOutQuint: function(t) {
            return 1 + (--t) * t * t * t * t;
        },
        easeInOutQuint: function(t) {
            return t < 0.5 ? 16 * t * t * t * t * t : 1 + 16 * (--t) * t * t * t * t;
        }
    };
    

    var getTimeNow = function() {
        return 'now' in window.performance ? performance.now() : new Date().getTime();
    };


    var scrollto = function(destination, duration, easing, callback) {

        // console.log("scrollto");
    
        duration = duration || 200;
        easing = easing || "linear";
    
        var startPosition = window.pageYOffset;
        var startTime = getTimeNow();
        
        var documentHeight = Math.max(document.body.scrollHeight, document.body.offsetHeight, document.documentElement.clientHeight, document.documentElement.scrollHeight, document.documentElement.offsetHeight);
        var windowHeight = window.innerHeight || document.documentElement.clientHeight || document.getElementsByTagName('body')[0].clientHeight;
        var destinationOffset = typeof destination === 'number' ? destination : destination.offsetTop;
        var destinationOffsetToScroll = Math.round(documentHeight - destinationOffset < windowHeight ? documentHeight - windowHeight : destinationOffset);
        
    
        if ('requestAnimationFrame' in window === false) {
            window.scroll(0, destinationOffsetToScroll);
            if (callback) { callback(); }
            return;
        }
        
        var animation = new Animation(function() {
            
            var now = getTimeNow();
            var time = Math.min(1, ((now - startTime) / duration));
            var timeFunction = easings[easing](time);
            window.scroll(0, Math.ceil((timeFunction * (destinationOffsetToScroll - startPosition)) + startPosition));
            
            if (window.pageYOffset === destinationOffsetToScroll) {
                if (callback) { callback(); }
                animation.stop();
            }
    
        });
    
        animation.start();
    
    };


    return scrollto;


})();

return {
    scrollto: scrollto
};

}));