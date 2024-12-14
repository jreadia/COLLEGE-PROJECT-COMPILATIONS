# Python program that creates visualizations based on the merged csv files

import pandas as pd
import matplotlib.pyplot as plt

# Load the merged CSV file - Location of the file may vary depending on the location of the file in your system
data = pd.read_csv('Pluscebo - Final Project/merged_data.csv')

# ============================== Visualization 1 ============================== #
# Question 1: What is percentage of each city area that is affected by flood hazards for 5, 25, and 100-year return periods?

# Calculate the mean of flood hazard in each city for 5, 25, and 100-year return periods
df_5_years_mean = data.groupby('adm3_en')[['pct_area_flood_hazard_5yr_low', 'pct_area_flood_hazard_5yr_med', 'pct_area_flood_hazard_5yr_high']].mean()
df_25_years_mean = data.groupby('adm3_en')[['pct_area_flood_hazard_25yr_low', 'pct_area_flood_hazard_25yr_med', 'pct_area_flood_hazard_25yr_high']].mean()
df_100_years_mean = data.groupby('adm3_en')[['pct_area_flood_hazard_100yr_low', 'pct_area_flood_hazard_100yr_med', 'pct_area_flood_hazard_100yr_high']].mean()

# Calculate the percentage of each city area that is affected by flood hazards for 5 years
df_5_years_mean.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of City Area Affected by Flood Hazards for 5-Year Return Period')
plt.xlabel('City')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each city area that is affected by flood hazards for 25 years
df_25_years_mean.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of City Area Affected by Flood Hazards for 25-Year Return Period')
plt.xlabel('City')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each city area that is affected by flood hazards for 100 years
df_100_years_mean.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of City Area Affected by Flood Hazards for 100-Year Return Period')
plt.xlabel('City')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()


# ============================== Visualization 2 ============================== #
# Question 2: What is the percentage of each city area that is affected by landslide hazards?

# Calculate the mean of landslide hazard in each city
df_landslide_mean = data.groupby('adm3_en')[['pct_area_landslide_hazard_low','pct_area_landslide_hazard_med','pct_area_landslide_hazard_high']].mean()

# Calculate the percentage of each city area that is affected by landslide hazards
df_landslide_mean.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of City Area Affected by Landslide Hazards')
plt.xlabel('City')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()


# ============================== Visualization 3 ============================== #
# Question 3: What is the percentage of each province area that is affected by flood hazards for 5, 25, and 100-year return periods?

# Calculate the mean of flood hazard in each province for 5, 25, and 100-year return periods
df_5_years_mean_province = data.groupby('adm2_en')[['pct_area_flood_hazard_5yr_low', 'pct_area_flood_hazard_5yr_med', 'pct_area_flood_hazard_5yr_high']].mean()
df_25_years_mean_province = data.groupby('adm2_en')[['pct_area_flood_hazard_25yr_low', 'pct_area_flood_hazard_25yr_med', 'pct_area_flood_hazard_25yr_high']].mean()
df_100_years_mean_province = data.groupby('adm2_en')[['pct_area_flood_hazard_100yr_low', 'pct_area_flood_hazard_100yr_med', 'pct_area_flood_hazard_100yr_high']].mean()

# Calculate the percentage of each province area that is affected by flood hazards for 5 years
df_5_years_mean_province.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Province Area Affected by Flood Hazards for 5-Year Return Period')
plt.xlabel('Province')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each province area that is affected by flood hazards for 25 years
df_25_years_mean_province.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Province Area Affected by Flood Hazards for 25-Year Return Period')
plt.xlabel('Province')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each province area that is affected by flood hazards for 100 years
df_100_years_mean_province.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Province Area Affected by Flood Hazards for 100-Year Return Period')
plt.xlabel('Province')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# ============================== Visualization 4 ============================== #
# Question 4: What is the percentage of each province area that is affected by landslide hazards?

# Calculate the mean of landslide hazard in each province
df_landslide_mean_province = data.groupby('adm2_en')[['pct_area_landslide_hazard_low','pct_area_landslide_hazard_med','pct_area_landslide_hazard_high']].mean()

# Calculate the percentage of each province area that is affected by landslide hazards
df_landslide_mean_province.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Province Area Affected by Landslide Hazards')
plt.xlabel('Province')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability  
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# ============================== Visualization 5 ============================== #
# Question 5: What is the percentage of each region area that is affected by flood hazards for 5, 25, and 100-year return periods?

# Calculate the mean of flood hazard in each region for 5, 25, and 100-year return periods
df_5_years_mean_region = data.groupby('adm1_en')[['pct_area_flood_hazard_5yr_low', 'pct_area_flood_hazard_5yr_med', 'pct_area_flood_hazard_5yr_high']].mean()
df_25_years_mean_region = data.groupby('adm1_en')[['pct_area_flood_hazard_25yr_low', 'pct_area_flood_hazard_25yr_med', 'pct_area_flood_hazard_25yr_high']].mean()
df_100_years_mean_region = data.groupby('adm1_en')[['pct_area_flood_hazard_100yr_low', 'pct_area_flood_hazard_100yr_med', 'pct_area_flood_hazard_100yr_high']].mean()

# Calculate the percentage of each region area that is affected by flood hazards for 5 years
df_5_years_mean_region.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Region Area Affected by Flood Hazards for 5-Year Return Period')
plt.xlabel('Region')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each region area that is affected by flood hazards for 25 years
df_25_years_mean_region.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Region Area Affected by Flood Hazards for 25-Year Return Period')
plt.xlabel('Region')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# Calculate the percentage of each region area that is affected by flood hazards for 100 years
df_100_years_mean_region.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Region Area Affected by Flood Hazards for 100-Year Return Period')
plt.xlabel('Region')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()

# ============================== Visualization 6 ============================== #
# Question 6: What is the percentage of each region area that is affected by landslide hazards?

# Calculate the mean of landslide hazard in each region
df_landslide_mean_region = data.groupby('adm1_en')[['pct_area_landslide_hazard_low','pct_area_landslide_hazard_med','pct_area_landslide_hazard_high']].mean()

# Calculate the percentage of each region area that is affected by landslide hazards
df_landslide_mean_region.plot(kind='bar', color=['blue', 'orange', 'green'])
plt.title('Percentage of Region Area Affected by Landslide Hazards')
plt.xlabel('Region')
plt.ylabel('Percentage of Area Affected')
plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
plt.tight_layout()  # Adjust layout to prevent clipping of labels
plt.show()
