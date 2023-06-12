function disable_form() {
    let input_arr = document.getElementsByTagName("input");
    for(let i = 0; i < input_arr.length; i++){
        input_arr[i].disabled = true;
    }
    let texterea_arr = document.getElementsByTagName("textarea");
    for(let j = 0; j < texterea_arr.length; j++){
        texterea_arr[j].disabled = true;
    }
}

function show_solution() {
    let temp = document.getElementsByClassName("solution");
    for(let i = 0; i < temp.length; i++){
        temp[i].setAttribute("style", "clear: both; display: block;");
    }
}
