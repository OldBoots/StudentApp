function func() {
    let arr_input = document.getElementsByTagName("input");
    for(let i = 0; i < arr_input.length; i++){
        arr_input[i].disabled = true;
    }
    let arr_texterea = document.getElementsByTagName("textarea");
    for(let j = 0; j < arr_input.length; j++){
        arr_texterea[j].disabled = true;
    }
} func();
