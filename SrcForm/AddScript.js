function add_input(id_task, i, j){
    let p_on_table = document.getElementById("table_" + id_task + "_" + i + "_" + j);
    let textarea = document.createElement("textarea");
    textarea.className = "field";
    textarea.id = "textarea_" + id_task;
    textarea.name = "textarea";
    p_on_table.appendChild(textarea);
    return 1;
}

function init_main_div(id_task, num_task){
    let main_div = document.createElement("div");
    main_div.id = "id_" + id_task;
    main_div.className = "maindiv";
    let task_number = document.createElement("span");
    task_number.innerHTML = "<b>№ " + num_task + "</b>";
    task_number.id = "task_number_id_" + num_task;
    main_div.appendChild(task_number);
    let answer_div = document.createElement("div");
    answer_div.id = "answer_" + id_task;
    answer_div.className = "answer";
    main_div.appendChild(answer_div);
    document.body.appendChild(main_div);
}

function init_solution(id_task){
    let main_div = document.getElementById("id_" + id_task)
    let solution = document.createElement("div");
    solution.className = "solution";
    let p_text_solution = document.createElement("p");
    p_text_solution.innerHTML = "Пояснение:";
    let p_solution = document.createElement("p");
    p_solution.id = "solution_" + id_task;
    solution.appendChild(p_text_solution);
    solution.appendChild(p_solution);
    main_div.appendChild(solution);
}

function init_pbody(id_task){
    let main_div = document.getElementById("id_" + id_task)
    let pbody_div = document.createElement("div");
    pbody_div.className = "pbody";
    pbody_div.id = "pbody_" + id_task;
    let p_text_task = document.createElement("p");
    p_text_task.innerHTML += "<b>Задание:</b>";
    let text_task = document.createElement("p");
    text_task.id = "text_" + id_task;
    p_text_task.appendChild(text_task);
    let p_image = document.createElement("p");
    p_image.id = "image_" + id_task;
    pbody_div.appendChild(p_text_task);
    pbody_div.appendChild(p_image);
    main_div.appendChild(pbody_div);
}

function create_task_number(id_task, num_task) {
    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "1";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let input_answer = document.createElement("input");
    input_answer.type = "number";
    input_answer.className = "number_field";
    input_answer.id = "input_answer_" + id_task;
    input_answer.name = "input";
    pbody_div.appendChild(input_answer);

    init_solution(id_task);
    return 1;
}

function create_task_string(id_task, num_task) {

    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "2";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let input_answer = document.createElement("input");
    input_answer.type = "text";
    input_answer.className = "string";
    input_answer.id = "input_answer_" + id_task;
    input_answer.name = "input";
    pbody_div.appendChild(input_answer);

    init_solution(id_task);
    return 1;
}

function create_task_comp(id_task, count_options, num_task){

    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "3";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let list_A = document.createElement("ol");
    list_A.type = "A";
    let list_1 = document.createElement("ol");
    list_1.type = "1";
    for(let i = 0; i < count_options; i++){
        let one_li_on_list_A = document.createElement("li");
        let one_p_on_list_A = document.createElement("p");
        one_p_on_list_A.id = "list_A_" + id_task + "_" + i;
        one_li_on_list_A.appendChild(one_p_on_list_A);
        list_A.appendChild(one_li_on_list_A);
    }
    for(let j = 0; j < count_options; j++){
        let one_li_on_list_1 = document.createElement("li");
        let one_p_on_list_1 = document.createElement("p");
        one_p_on_list_1.id = "list_1_" + id_task + "_" + j;
        one_li_on_list_1.appendChild(one_p_on_list_1);
        list_1.appendChild(one_li_on_list_1);
    }

    let table = document.createElement("table");
    let trow1 = document.createElement("tr");
    let trow2 = document.createElement("tr");

    for(let ti = 0; ti < count_options; ti++){
        let td1 = document.createElement("td");
        td1.innerHTML = String.fromCharCode(65 + ti);
        trow1.appendChild(td1);
        let input = document.createElement("input");
        input.className = "table_number_field";
        input.type = "number";
        input.name = "input";
        let td2 = document.createElement("td");
        td2.appendChild(input);
        trow2.appendChild(td2);
    }
    table.appendChild(trow1);
    table.appendChild(trow2);

    pbody_div.appendChild(list_A);
    pbody_div.appendChild(list_1);
    pbody_div.appendChild(table);

    init_solution(id_task);
    return 1;
}

function create_task_seq(id_task, count_options, num_task){

    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "4";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let list_1 = document.createElement("ol");
    list_1.type = "1";
    for(let j = 0; j < count_options; j++){
        let one_li_on_list_1 = document.createElement("li");
        let one_p_on_list_1 = document.createElement("p");
        one_p_on_list_1.id = "list_1_" + id_task + "_" + j;
        one_li_on_list_1.appendChild(one_p_on_list_1);
        list_1.appendChild(one_li_on_list_1);
    }
    pbody_div.appendChild(list_1);


    let input_answer = document.createElement("input");
    input_answer.type = "number";
    input_answer.className = "number_field";
    input_answer.id = "input_answer_" + id_task;
    input_answer.name = "input";
    pbody_div.appendChild(input_answer);

    init_solution(id_task);
    return 1;
}

function create_task_table_string(id_task, count_rows, count_cols, num_task){
    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "5";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let body_table = document.createElement("table");
    for(let i = 0; i < count_rows; i++){
        let one_row_block = document.createElement("tr");
        for(let j = 0; j < count_cols; j++){
            let p_on_table = document.createElement("p");
            let one_col_table = document.createElement("td");
            p_on_table.id = "table_" + id_task + "_" + i + "_" + j;
            p_on_table.className = "table_field";
            one_col_table.appendChild(p_on_table);
            one_row_block.appendChild(one_col_table);
        }
        body_table.appendChild(one_row_block);
    }
    pbody_div.appendChild(body_table);

    init_solution(id_task);
    return 1;
}

function create_task_multi(id_task, count_options, num_task){
    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "6";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    for(let i = 0; i < count_options; i++){
        let checkbox = document.createElement("input");
        checkbox.className = "checkbox_field";
        checkbox.type = "checkbox";
        checkbox.name = "checkbox";
        checkbox.id = "checkbox_" + id_task + "_" + i;
        let p = document.createElement("p");
        p.id = "opt_" + id_task + "_" + i;
        let option = document.createElement("div");
        option.appendChild(checkbox);
        option.appendChild(p);
        option.setAttribute("style", "display:flex; flex-direction: row;");
        pbody_div.appendChild(option);
    }

    init_solution(id_task);
    return 1;
}

function create_task_28line(id_task, num_task) {
    init_main_div(id_task, num_task);
    let main_div = document.getElementById("id_" + id_task);

    let answer_iRNA_div = document.createElement("div");
    answer_iRNA_div.id = "answer_iRNA_" + id_task;
    answer_iRNA_div.className = "answer_iRNA";
    main_div.appendChild(answer_iRNA_div);

    let type_div = document.createElement("div");
    type_div.id = "type_" + id_task;
    type_div.className = "type";
    type_div.innerHTML = "7";
    main_div.appendChild(type_div);

    init_pbody(id_task);
    let pbody_div = document.getElementById("pbody_" + id_task);

    let p_text_answer = document.createElement("p");
    p_text_answer.innerHTML = "<b>Ход решения:</b>";
    pbody_div.appendChild(p_text_answer);
    let textarea = document.createElement("textarea");
    textarea.className = "area";
    textarea.id = "textarea_" + id_task;
    textarea.name = "textarea";
    pbody_div.appendChild(textarea);

    let p_answer_iRNA_text = document.createElement("p");
    p_answer_iRNA_text.innerHTML = "<b>иРНК:</b>";
    pbody_div.appendChild(p_answer_iRNA_text);

    let div_iRNA = document.createElement("div");
    let p_5 = document.createElement("p");
    p_5.innerHTML = "5'- ";
    p_5.setAttribute("style", "display: inline-block");
    let p_3 = document.createElement("p");
    p_3.innerHTML = " -3'";
    p_3.setAttribute("style", "display: inline-block");
    let input_iRNA = document.createElement("input");
    input_iRNA.setAttribute("style", "display: inline-block");
    input_iRNA.id = "input_iRNA_" + id_task;
    input_iRNA.className = "string";
    input_iRNA.name = "input";
    div_iRNA.appendChild(p_5);
    div_iRNA.appendChild(input_iRNA);
    div_iRNA.appendChild(p_3);
    pbody_div.appendChild(div_iRNA);

    let p_answer_poly_text = document.createElement("p");
    p_answer_poly_text.innerHTML = "<b>Полипептидная цепочка(фрагмент белка):</b>";
    pbody_div.appendChild(p_answer_poly_text);

    let input_poly = document.createElement("input");
    input_poly.className = "string";
    input_poly.id = "input_poly_" + id_task;
    input_poly.name = "input";
    pbody_div.appendChild(input_poly);

    return 1;
}
