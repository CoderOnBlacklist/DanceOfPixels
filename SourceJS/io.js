var
key_left=0,
key_right=0;
document.addEventListener('keydown', function(event) {
    if(event.keyCode == 37) {
        key_left=1;
    }
    else if(event.keyCode == 39) {
        key_right=1;
    }
});
document.addEventListener('keyup', function(event) {
    if(event.keyCode == 37) {
        key_left=0;
    }
    else if(event.keyCode == 39) {
        key_right=0;
    }
});