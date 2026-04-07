import flet as ft 

def main_page(page: ft.Page):
    page.title = 'Мое первое приложение'
    page.theme_mode = ft.ThemeMode.LIGHT

    def text_name(e):  # e - event | "_" 
        text_hello.value = f"Добро пожаловать! {text_input.value}"
        name = text_input.value.strip()
        text_hello.value = None

        if name:
           text_hello.value = f"hello {name}"
        else:
            text_hello.value = "Введи имя быстрее пожалуйста плиз!!!" 
            text_hello.color = ft.Colors.RED_900

        page.update()

    text_hello = ft.Text('Hello', color=ft.Colors.RED)
    text_input = ft.TextField(label='Введите свое имя')
    btn = ft.Button('send', icon=ft.Icons.SEND, on_click=text_name)

    def themode(e):
        if page.theme_mode == ft.ThemeMode.DARK:
            page.theme_mode = ft.ThemeMode.LIGHT
        else:
            page.theme_mode = ft.ThemeMode.DARK
        page.update()
    page.add(text_hello, text_input, btn, theme_btn)


ft.app(main_page, view=ft.AppView.WEB_BROWSER)