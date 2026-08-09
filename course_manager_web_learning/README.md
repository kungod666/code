# course_manager_web_learning

这是 `course_manager` 的本机 Web 学习版。

它不使用 Cookie / Session。登录成功后，浏览器里的 JavaScript 用变量 `currentUserId` 保存当前 `user_id`，之后每个请求都主动带上 `user_id`。

## 运行

```powershell
cd D:\7-Zip\code\course_manager_web_learning
.\run.bat
```

然后浏览器打开：

```text
http://127.0.0.1:8088/
```

## 路由

```text
GET  /                    返回 HTML 页面
POST /api/login            登录；如果用户不存在则自动注册
GET  /api/settings         读取设置
POST /api/settings         保存设置
GET  /api/tasks            读取任务
POST /api/tasks            新增任务
POST /api/tasks/delete     删除任务
POST /api/tasks/done       标记任务完成
```

## 对照原控制台版

原来控制台版：

```text
cin 读取菜单数字
switch 分支执行 SQL
cout 输出结果
```

这个 Web 版：

```text
recv 读取 HTTP 请求
根据 method + path 路由执行 SQL
send 返回 HTML / JSON
```
