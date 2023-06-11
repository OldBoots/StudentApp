function create_task_number(id_task) {
    let main_div = document.createElement("div");
    main_div.id = "main_div_" + id_task;
    let pbody_div = document.createElement("div");
    pbody_div.className = "pbody";
    let p_text_task = document.createElement("p");
    p_text_task.innerHTML += "<b>Задание:</b>";
    let text_task = document.createElement("p");
    text_task.id = "text_" + id_task;
    p_text_task.appendChild(text_task);
    let p_image = document.createElement("p");
    p_image.id = "image_" + id_task;
    let input_answer = document.createElement("input");
    input_answer.innerHTML = "Ответ: ";
    input_answer.id = "answer_" + id_task;
    input_answer.type = "number";
    input_answer.className = "number_field";
    pbody_div.appendChild(p_text_task);
    pbody_div.appendChild(p_image);
    pbody_div.appendChild(input_answer);
    let solution = document.createElement("div");
    solution.setAttribute("style", "clear: both; display: block;");
    let p_text_solution = document.createElement("p");
    p_text_solution.innerHTML = "Пояснение:";
    let p_solution = document.createElement("p");
    p_solution.id = "solution_" + id_task;
    solution.appendChild(p_text_solution);
    solution.appendChild(p_solution);

    main_div.appendChild(pbody_div);
    main_div.appendChild(solution);
    let block = document.getElementById("num");
    block.appendChild(main_div);
}
