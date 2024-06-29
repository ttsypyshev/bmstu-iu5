import { accessToken, version } from "./consts.js";

// Класс для формирования URL для запросов к API
class Urls {
    constructor() {
        this.url = 'https://api.vk.com/method';
        this.commonInfo = `access_token=${accessToken}&v=${version}`;
    }

    // Метод для получения URL запроса информации о пользователе
    getUserInfo(userId) {
        if (!userId) {
            console.error("Не указан userId для getUserInfo");
            return null;
        }
        return `${this.url}/users.get?user_ids=${userId}&fields=photo_400_orig,sex,bdate,country,city,occupation&${this.commonInfo}`;
    }

    // Метод для получения URL запроса участников группы
    getGroupMembers(groupId, filter) {
        if (!groupId) {
            console.error("Не указан groupId для getGroupMembers");
            return null;
        }
        const filterString = filter ? `&filter=${filter}` : '';
        return `${this.url}/groups.getMembers?group_id=${groupId}&fields=photo_400_orig&${this.commonInfo}${filterString}`;
    }
}

export const urls = new Urls();
