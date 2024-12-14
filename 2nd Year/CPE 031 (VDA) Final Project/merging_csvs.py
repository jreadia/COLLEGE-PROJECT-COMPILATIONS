# Python Program to merge csv files before making a visualization
import pandas as pd

# Load the CSV files - Location of the files may vary depending on the location of the files in your system
hazards_df = pd.read_csv('Pluscebo - Final Project\Data from Kaggle\project_noah_hazards.csv')
locations_df = pd.read_csv('Pluscebo - Final Project\Data from Kaggle\location.csv')

# Merge the dataframes on 'adm4_pcode'
merged_df = pd.merge(hazards_df, locations_df, on='adm4_pcode', how='left')

# Select and rearrange columns
columns = [
    'adm4_pcode', 'adm4_en', 'adm3_pcode', 'adm3_en', 'adm2_pcode', 'adm2_en', 
    'adm1_pcode', 'adm1_en', 'brgy_total_area'
] + [col for col in hazards_df.columns if col != 'adm4_pcode']

merged_df = merged_df[columns]

# Save the merged dataframe to a new CSV file
merged_df.to_csv('merged_data.csv', index=False)