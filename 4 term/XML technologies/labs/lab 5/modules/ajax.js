class Ajax {
    // Метод для выполнения POST-запроса на указанный URL
    async post(url) {
        try {
            // Выполняем POST-запрос
            const response = await fetch(url, { method: 'POST' });
            // Проверяем успешность запроса
            if (!response.ok) {
                throw new Error(`Ошибка AJAX запроса: ${response.status} ${response.statusText}`);
            }
            // Получаем данные в формате JSON
            const data = await response.json();
            return data;
        } catch (error) {
            console.error(error.message);
            // Уведомляем пользователя об ошибке
            alert(`Произошла ошибка при выполнении запроса: ${error.message}`);
            return null;
        }
    }

    // Метод для выполнения GET-запроса на указанный URL
    async get(url) {
        try {
            // Выполняем GET-запрос
            const response = await fetch(url);
            // Проверяем успешность запроса
            if (!response.ok) {
                throw new Error(`Ошибка AJAX запроса: ${response.status} ${response.statusText}`);
            }
            // Получаем данные в формате JSON
            const data = await response.json();
            return data;
        } catch (error) {
            console.error(error.message);
            // Уведомляем пользователя об ошибке
            alert(`Произошла ошибка при выполнении запроса: ${error.message}`);
            return null;
        }
    }
}

export const ajax = new Ajax();
