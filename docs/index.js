(function() {


    var nodes = document.querySelectorAll(".navigator ul li");

    [].slice.call(nodes).forEach(function(node) {
        node.addEventListener("click", function() {

            var scrolldata = this.getAttribute('data-scrollto');

            var scrolltarget = document.querySelector(".section_" + scrolldata);

            UTILS.scrollto(
                scrolltarget,
                800,
                'easeOutQuad'
            );

        }); 
    });
    
})();