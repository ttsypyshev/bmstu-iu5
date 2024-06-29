class Ajax {
    async get(url) {
        try {
            const resp = await fetch(url);
            if (!resp.ok) throw new Error(`HTTP error! status: ${resp.status}`);
            return await resp.json();
        } catch (error) {
            console.error("Fetch GET error:", error);
            return null;
        }
    }

    async post(url, content) {
        try {
            const resp = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(content)
            });
            if (!resp.ok) throw new Error(`HTTP error! status: ${resp.status}`);
            return await resp.json();
        } catch (error) {
            console.error("Fetch POST error:", error);
            return null;
        }
    }

    async delete(url) {
        try {
            const resp = await fetch(url, {
                method: 'DELETE'
            });
            if (!resp.ok) throw new Error(`HTTP error! status: ${resp.status}`);
            return await resp.json();
        } catch (error) {
            console.error("Fetch DELETE error:", error);
            return null;
        }
    }
}

export const ajax = new Ajax();
