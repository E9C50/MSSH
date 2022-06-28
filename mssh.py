import os
import sys

import pandas as pd
import prettytable as pt

config_file_path = '~/.server.csv'


def print_help_info():
    server_table = pt.PrettyTable(['命令', '示例', '说明'])
    server_table.add_row(['ls', 'mssh ls', '查看服务器列表'])
    server_table.add_row(['help', 'mssh help', '帮助文档'])
    server_table.add_row(['conn', 'mssh conn DEV_HOST', '通过名称连接服务器'])
    server_table.add_row(['coip', 'mssh conn 192.168.1.1', '通过IP地址连接服务器'])

    server_table.align = 'l'
    print(server_table)


def print_server_list():
    server_df = pd.read_csv(config_file_path)
    server_df = server_df.sort_values(by='name')
    server_table = pt.PrettyTable(['服务器名称', '服务器地址', '服务器端口', '登录用户名', '服务器说明'])
    for index, server in server_df.iterrows():
        server_table.add_row([server['name'], server['address'], server['port'], server['user'], server['remark']])
    print(server_table)


def connect_to_remote(address, port, username, password):
    os.system("sshpass -p {} ssh {}@{} -p{}".format(password, username, address, port))


def connect_by_name(name):
    server_df = pd.read_csv(config_file_path)
    for index, server in server_df.iterrows():
        if server['name'] == name:
            connect_to_remote(server['address'], server['port'], server['user'], server['password'])
            break


def connect_by_address(address):
    server_df = pd.read_csv(config_file_path)
    for index, server in server_df.iterrows():
        if server['address'] == address:
            connect_to_remote(server['address'], server['port'], server['user'], server['password'])
            break


if __name__ == '__main__':
    if len(sys.argv) == 1 or sys.argv[1] == 'help':
        print_help_info()
    elif sys.argv[1] == 'ls':
        print_server_list()
    elif sys.argv[1] == 'conn':
        connect_by_name(sys.argv[2])
    elif sys.argv[1] == 'coip':
        connect_by_address(sys.argv[2])
