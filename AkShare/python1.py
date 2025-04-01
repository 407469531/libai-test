import akshare as ak

# 获取上证指数的历史行情数据
stock_zh_index_daily_df = ak.stock_zh_index_daily(symbol="sh000001")
print(stock_zh_index_daily_df)