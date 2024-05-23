class Ajax {
    // Метод для выполнения GET-запроса
    async get(url) {
        try {
            const response = await fetch(url);
            if (!response.ok) {
                throw new Error(`Ошибка AJAX запроса: ${response.status} ${response.statusText}`);
            }
            const result = await response.json();
            return result;
        } catch (error) {
            console.error(error.message);
            alert(`Произошла ошибка при выполнении запроса: ${error.message}`);
            return null;
        }
    }

    // Метод для выполнения POST-запроса
    async post(url, content) {
        try {
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(content)
            });
            if (!response.ok) {
                throw new Error(`Ошибка AJAX запроса: ${response.status} ${response.statusText}`);
            }
            const result = await response.json();
            return result;
        } catch (error) {
            console.error(error.message);
            alert(`Произошла ошибка при выполнении запроса: ${error.message}`);
            return null;
        }
    }

    // Метод для выполнения DELETE-запроса
    async delete(url) {
        try {
            const response = await fetch(url, {
                method: 'DELETE'
            });
            if (!response.ok) {
                throw new Error(`Ошибка AJAX запроса: ${response.status} ${response.statusText}`);
            }
            const result = await response.json();
            return result;
        } catch (error) {
            console.error(error.message);
            alert(`Произошла ошибка при выполнении запроса: ${error.message}`);
            return null;
        }
    }
}

export const ajax = new Ajax();
