from pyecharts import options as opts
from pyecharts.charts import Timeline,Sunburst
import pandas as pd

citys=["杭州",'湖州','嘉兴','金华','丽水','宁波','衢州','绍兴','台州','温州','舟山']
levels=["优","良","轻度污染","重度污染"]
tl=Timeline(init_opts=opts.InitOpts("1000px", height="600px"))
datas=[{'name': '杭州', 'children': [{'name': '良', 'value': 205}, {'name': '轻度污染', 'value': 97}, {'name': '优', 'value': 43}, {'name': '中度污染', 'value': 13}, {'name': '重度污染', 'value': 7}]}, {'name': '湖州', 'children': [{'name': '良', 'value': 185}, {'name': '轻度污染', 'value': 103}, {'name': '优', 'value': 45}, {'name': '中度污染', 'value': 22}, {'name': '重度污染', 'value': 8}, {'name': '严重污染', 'value': 2}]}]
for i in range(2014,2019):
    df=pd.read_excel('/home/null/repos/Python/aqi数据.xlsx',sheet_name='{}年'.format(i))
    data=[]
    for city in citys:
        city_data = df.loc[df['city'] == city]
        city_dict={}
        childern=[]
        city_dict["name"]=city
        #city_dict["itemStyle"]= {"color": "#d0545f"}
        values=dict(city_data["质量等级"].value_counts())
        sum=0
        for name,value in zip(values.keys(),values.values()):
            k={}
            if "污染" in name:
                #sum+=int(value)
                k["itemStyle"]={"color":"red"}
            if "良" in name:
                k["itemStyle"] = {"color": "orange"}
            if "优" in name:
                k["itemStyle"] = {"color": "green"}
            k["name"]=name
            k["value"]=int(value)
            #k["itemStyle"] = {"color": "#d0545f"}
            childern.append(k)
        city_dict["children"]=childern
        #city_dict["value"]=sum
        data.append(city_dict)
    print(data)
    sun=(
        Sunburst(init_opts=opts.InitOpts("1000px", height="600px"))
        .add("空气质量",data_pair=data)
        .set_global_opts(title_opts=opts.TitleOpts(title="{}年空气质量".format(i)))

    )
    tl.add(sun, "{}年".format(i))
tl.render("Aqi数据.html")

