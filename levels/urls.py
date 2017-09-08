from django.conf.urls import url

from . import views

app_name = 'levels'
urlpatterns = [
    url(r'^get_file/(.+)/$', views.get_file, name='get_file'),
    url(r'^list_files/$', views.list_files_endpoint, name='list_files'),
    url(r'^save_file/$', views.save_file, name='save_file'),
    url(r'^new_file/$', views.new_file, name='new_file'),
    url(r'^delete_file/$', views.delete_file, name='delete_file'),
    url(r'^rename_file/$', views.rename_file, name='rename_file'),
    url(r'^duplicate_file/$', views.duplicate_file, name='duplicate_file'),
    url(r'^', views.index, name='index'),
]

