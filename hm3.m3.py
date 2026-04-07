import flet as ft

def main(page: ft.Page):
    page.title = "Проверка возраста"

    input_age = ft.TextField(label="Введите ваш возраст")
    result_text = ft.Text()

    def check_age(e):
        age_value = input_age.value

        if not age_value or not age_value.isdigit():
            result_text.value = "Введите корректный возраст"
            result_text.color = ft.Colors.YELLOW

        else:
            age = int(age_value)

            if age >= 18:
                result_text.value = "Доступ разрешен"
                result_text.color = ft.Colors.GREEN
            else:
                result_text.value = "Доступ запрещен"
                result_text.color = ft.Colors.RED

        page.update()

    check_button = ft.Button("Проверить", on_click=check_age)

    page.add(input_age, check_button, result_text)

ft.run(main)