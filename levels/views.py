import os
import json

import shutil
from django.shortcuts import render
from django.http import HttpResponse, Http404, JsonResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt

BASE_DIR = os.path.dirname(os.path.dirname(__file__))
LEVELS_DIR = BASE_DIR + os.sep + "stored_levels" + os.sep


def index(request):
    print("Accessing index")
    context = {
        'files': list_files(LEVELS_DIR)
    }

    return render(request, 'levels/index.html', context)


def list_files(directory):
    d = []
    for file in os.listdir(directory):
        if not file.startswith("."):
            d.append(file)
    return d

def list_files_endpoint(request):
    return JsonResponse({"success": True, "files_list": list_files(LEVELS_DIR)})

def get_file(request, file):
    print("You are trying to get the file: " + file)
    contents = {
        "success": True
    }
    print(LEVELS_DIR + file)
    with open(LEVELS_DIR + file, 'r') as file:
        contents["file"] = file.read()
    return JsonResponse(contents)


def save_file(request):
    print("Trying to save file!")
    if request.method == 'POST':
        bodyjson = json.loads(request.body.decode('utf-8'))
        with open(LEVELS_DIR + bodyjson['filename'], 'w') as file:
            file.write(bodyjson['data'])
    else:
        return JsonResponse({"success": False, "message": "Request not send with POST"})

    response = {
        "success": True
    }

    return JsonResponse(response)


def new_file(request):
    if request.method == 'POST':
        bodyjson = json.loads(request.body.decode('utf-8'))
        if bodyjson['filename'] in list_files(LEVELS_DIR):
            return JsonResponse({"success": False, "message": "File already exists"})
        else:
            with open(LEVELS_DIR + bodyjson['filename'], 'a') as file:
                with open(LEVELS_DIR + ".template.lvl", 'r') as templateFile:
                    file.write(templateFile.read())
            return JsonResponse({"success": True, "files_list": list_files(LEVELS_DIR)})
    else:
        return JsonResponse({"success": False, "message": "Request not send with POST"})


def delete_file(request):
    if request.method == 'POST':
        bodyjson = json.loads(request.body.decode('utf-8'))
        if bodyjson['filename'] in list_files(LEVELS_DIR):
            os.remove(LEVELS_DIR + bodyjson['filename'])
            return JsonResponse({"success": True, "files_list": list_files(LEVELS_DIR)})
        else:
            return JsonResponse({"success": False, "message": "File does not exist"})
    else:
        return JsonResponse({"success": False, "message": "Request not send with POST"})

def rename_file(request):
    if request.method =='POST':
        bodyjson = json.loads(request.body.decode('utf-8'))
        if (bodyjson['filename'] in list_files(LEVELS_DIR)):
            os.rename(LEVELS_DIR + bodyjson['filename'], LEVELS_DIR + bodyjson['newfilename'])
            return JsonResponse({"success": True, "files_list": list_files(LEVELS_DIR)})
        else:
            return JsonResponse({"success": False, "message": "File does not exist"})
    else:
        return JsonResponse({"success": False, "message": "Request not send with POST"})

def duplicate_file(request):
    if request.method =='POST':
        bodyjson = json.loads(request.body.decode('utf-8'))
        if (bodyjson['filename'] in list_files(LEVELS_DIR)):
            shutil.copy(LEVELS_DIR + bodyjson['filename'], LEVELS_DIR + bodyjson['newfilename'])
            return JsonResponse({"success": True, "files_list": list_files(LEVELS_DIR)})
        else:
            return JsonResponse({"success": False, "message": "File does not exist"})
    else:
        return JsonResponse({"success": False, "message": "Request not send with POST"})
# Create your views here.
