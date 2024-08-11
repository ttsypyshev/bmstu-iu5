class Ajax {
    post(url, callback) {
        let xhr = new XMLHttpRequest();
        xhr.open('POST', url);
        xhr.send();

        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                if (xhr.status === 200) {
                    const data = JSON.parse(xhr.response);
                    callback(data);
                } else {
                    // Обрабатываем ошибку
                    console.error("Ошибка AJAX запроса:", xhr.status, xhr.statusText);
                    // Можно добавить уведомление пользователю
                }
            }
        };
    }
}

export const ajax = new Ajax();