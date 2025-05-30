import streamlit as st
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix, roc_auc_score
from sklearn.preprocessing import LabelBinarizer

# Установка шрифтов для корректного отображения кириллицы
plt.rcParams['font.family'] = 'DejaVu Sans' # Можно изменить на 'Arial' или другой, если установлен
plt.rcParams['axes.unicode_minus'] = False # Для корректного отображения знака минус

st.set_page_config(
    page_title="Классификация Ирисов с RandomForest",
    page_icon="🌸",
    layout="wide"
)

st.title("Приложение для классификации Ирисов")
st.markdown("---")

# 1. Загрузка данных
@st.cache_data
def load_data():
    iris = load_iris()
    X = pd.DataFrame(iris.data, columns=iris.feature_names)
    y = pd.Series(iris.target)
    y_labels = pd.Series(iris.target_names[y])
    return X, y_labels, iris.target_names, iris.feature_names

X, y, target_names, feature_names = load_data()

# Разделение данных на обучающую и тестовую выборки
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42, stratify=y
)

st.sidebar.header("Настройка Модели")

# 2. Выбор модели и настройка гиперпараметров (для RandomForestClassifier)
st.sidebar.subheader("RandomForestClassifier Гиперпараметры")

n_estimators = st.sidebar.slider(
    "Количество деревьев (n_estimators)", 10, 300, 100, 10
)
max_depth = st.sidebar.slider(
    "Максимальная глубина дерева (max_depth)", 1, 20, 10
)
if st.sidebar.checkbox("Без ограничения глубины (None)"):
    max_depth = None

# Создание пайплайна с предобработкой и моделью
# Предобработка: масштабирование числовых признаков
numerical_transformer = StandardScaler()

preprocessor = Pipeline(steps=[
    ('scaler', numerical_transformer)
])

# Определение модели с выбранными гиперпараметрами
model = RandomForestClassifier(
    n_estimators=n_estimators,
    max_depth=max_depth,
    random_state=42,
    n_jobs=-1 # Используем все доступные ядра
)

# Объединение препроцессора и модели в один пайплайн
full_pipeline = Pipeline(steps=[
    ('preprocessor', preprocessor),
    ('classifier', model)
])

st.sidebar.markdown("---")
st.sidebar.info("Измените гиперпараметры, чтобы перестроить модель и увидеть, как это влияет на производительность.")

st.header("1. Обучение Модели")
st.write(f"Обучаем **RandomForestClassifier** с `n_estimators={n_estimators}` и `max_depth={max_depth if max_depth is not None else 'None'}`.")

# 3. Обучение модели
full_pipeline.fit(X_train, y_train)

st.success("Модель успешно обучена!")

# 4. Оценка модели
st.header("2. Оценка Производительности Модели")

y_pred = full_pipeline.predict(X_test)
y_prob = full_pipeline.predict_proba(X_test)

col1, col2 = st.columns(2)

with col1:
    st.subheader("Основные Метрики")
    st.write(f"**Точность (Accuracy):** `{accuracy_score(y_test, y_pred):.4f}`")

    # Преобразование y_test в бинарный формат для ROC AUC
    lb = LabelBinarizer()
    y_test_binarized = lb.fit_transform(y_test)

    # ROC AUC для многоклассовой классификации (OVR - One-vs-Rest)
    try:
        roc_auc = roc_auc_score(y_test_binarized, y_prob, multi_class='ovr', average='weighted')
        st.write(f"**ROC AUC (Weighted OvR):** `{roc_auc:.4f}`")
    except ValueError:
        st.warning("Недостаточно классов для расчета ROC AUC или проблема с предсказанными вероятностями.")


with col2:
    st.subheader("Отчет о Классификации")
    report_df = pd.DataFrame(classification_report(y_test, y_pred, output_dict=True)).T
    st.dataframe(report_df.style.highlight_max(axis=0))

st.subheader("Матрица Ошибок (Confusion Matrix)")
cm = confusion_matrix(y_test, y_pred, labels=target_names)
fig_cm, ax_cm = plt.subplots(figsize=(8, 6))
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", cbar=False,
            xticklabels=target_names, yticklabels=target_names, ax=ax_cm)
ax_cm.set_xlabel("Предсказанный класс")
ax_cm.set_ylabel("Истинный класс")
ax_cm.set_title("Матрица ошибок")
st.pyplot(fig_cm)


st.subheader("Важность Признаков")
# Важность признаков доступна через .named_steps['classifier'] для пайплайна
feature_importances = full_pipeline.named_steps['classifier'].feature_importances_
importance_df = pd.DataFrame({
    'Признак': feature_names,
    'Важность': feature_importances
}).sort_values(by='Важность', ascending=False)

fig_fi, ax_fi = plt.subplots(figsize=(10, 6))
sns.barplot(x='Важность', y='Признак', data=importance_df, ax=ax_fi, palette='viridis')
ax_fi.set_title("Важность признаков в RandomForestClassifier")
ax_fi.set_xlabel("Важность")
ax_fi.set_ylabel("Признак")
st.pyplot(fig_fi)

st.header("3. Сделать Предсказание для Нового Ириса")
st.markdown("Введите значения характеристик ириса для получения предсказания его вида.")

# 5. Пользовательский ввод для предсказания
input_values = {}
for feature in feature_names:
    min_val = X[feature].min()
    max_val = X[feature].max()
    avg_val = X[feature].mean()
    input_values[feature] = st.slider(
        f"Введите {feature} (см)",
        min_value=float(min_val),
        max_value=float(max_val),
        value=float(avg_val),
        step=0.1
    )

if st.button("Предсказать вид ириса"):
    input_df = pd.DataFrame([input_values])
    st.write("Введенные данные:")
    st.dataframe(input_df)

    prediction = full_pipeline.predict(input_df)
    prediction_proba = full_pipeline.predict_proba(input_df)

    st.subheader("Результат Предсказания")
    st.success(f"Предсказанный вид ириса: **{prediction[0]}**")

    st.subheader("Вероятности классов")
    proba_df = pd.DataFrame(prediction_proba, columns=target_names)
    st.dataframe(proba_df.T.rename(columns={0: 'Вероятность'}))

st.markdown("---")
st.caption("Разработано для НИРС по дисциплине «Технологии машинного обучения»")